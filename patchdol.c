#include "patchdol.h"

// GCC est assez proche de SN, au niveau de l'assembleur inline
#define __SN__

// il y aura quand même besoin de modifier certains fichiers du SDK qui n'utilise pas le même assembleur inline que GCC...
   //#include "dolphin.h" // dolphin sdk

// Si vous n'avez pas le SDK de dolphin, décommentez la ligne en dessous
#include "folphin.h"

#include "windwaker.h"

extern unsigned char __begin[]; // début
extern unsigned char __end[]; // et fin du binaire, toute section confondues. Utilisé pour calculer la taille nécessaire et réallouer la pile
// du thread principal

typedef void(*fun_t)();

dCcD_Stts colstat; // dCcD_Stts dérive de dCcD_GStts
dCcD_Sph col; // dCcD_GObjInf dérive de dCcD_Sph, mais a une taille identique, donc on recycle

// pointeur vers la dernière flèche qui a été arrêtée
arrow *arr;
// direction dans laquelle faire varier le compteur de rubis
int dir;

// instance du thread utilisé pour exécuter threaded
OSThread mt;
// pile du thread
u8 mts[4096];
//OSAlarm alarm;
// Queue de threads réveillée dès qu'une opération audio complète? l'important c'est qu'elle soit réveillée assez fréquemment pour être utile
extern OSThreadQueue AudioQueue;
// l'état des 4 manettes
extern PADStatus padstatus[4];

void monkeypatch_far(void *addr, unsigned target); // Inserts a longcall to target
void monkeypatch_close(void *addr, unsigned target); // Inserts a closecall to target 

void onArrowHit();

void mymain();
void fix_default_thread();

__attribute__ ((section (".entry")))
void patch_entry_point() {
	// point d'entrée du binaire
	fix_default_thread();
	monkeypatch_close((void*)(0x80003270), (unsigned)mymain);
	original_entry();
}

void __last();

void fix_default_thread() {
	unsigned sz = __end - __begin;
	sz = (sz + 3) & ~3;
	unsigned defthread = (unsigned)patch_entry_point;
	defthread += sz;
	// l'adresse des piles et thread sont hardcodé, donc il faut patcher les instructions
	ppc_instruction *inst = (void*)0x80307954;
	inst[0] = ADDIS(3, 0, defthread);
	inst[2] = ADDI(0, 3, defthread);

	defthread += 0x10000; // stack end
	inst = (void*)0x8030794C;
	inst[0] = ADDIS(3, 0, defthread);
	inst[1] = ADDI(0, 3, defthread);

	inst = (void*)0x80301854;
	inst[0] = ADDIS(3, 0, defthread);
	inst[1] = ADDI(3, 3, defthread);

	inst = (void*)0x80003278;
	inst[0] = ADDIS(1, 0, defthread);
	inst[1] = ADDI(1, 1, defthread);
}

void monkeypatch_close(void *addr, unsigned tadr) {
	ppc_instruction *iadr = addr;
	unsigned diff = tadr - (unsigned)addr;
	diff >>= 2;
	iadr[0] = BL(diff);
}

void monkeypatchb_close(void *addr, unsigned tadr) {
	ppc_instruction *iadr = addr;
	unsigned diff = tadr - (unsigned)addr;
	diff >>= 2;
	iadr[0] = B(diff);
}

// séquence d'appel lourde.
// inutilisée
void monkeypatch_far(void *addr, unsigned tadr) {
	ppc_instruction *iadr = addr;

	iadr[0] = ADDIS(3, 0, tadr);
	iadr[1] = ADDI(3, 3, tadr);
	iadr[2] = MTCTR(3);//
	iadr[3] = BCTRL;
}

void mi_memset(void *a, unsigned char v, unsigned n){
	unsigned char *d = a;
	unsigned i = 0;
	while (i < n)
		d[i++] = v;
}

/*
  Ce code est exécuté sur un thread séparé parce qu'injecter ce code dans l'executable du jeu 
  necessite de faire attention aux locations, et donc d'écrire en pur assembleur
 */
void periodic() {
	if (padstatus[0].button & PAD_BUTTON_A) {
		// displayed by 803CA7CE
		//unsigned short * const dispruppes = (void*)0x803C4C0C;
		extern unsigned short currentruppes;
		extern int rupeesvariation;
		if (currentruppes >= 200) {
			dir = -1;
		} else if (currentruppes <= 0) {
			dir = 1;
		}
		rupeesvariation = dir;
	}
	if (arr) {
		OSReport("Requested to spawn explosion, clearing up...");
		
		cXyz scale = {2.5f, 2.5f, 2.5f};

		// Pas sur d'à quoi servent le double appel de set et setBombSmoke, mais c'est comme ca que fait le jeu...
		set(effect_manager, 1, 0xb, &arr->pos, 0, 0,-1, 0, -1, 0, 0, 0);
		setBombSmoke(effect_manager, 0x2009, &arr->pos, 0, &scale, -1);

		// explosion circle
		setBombSmoke(effect_manager, 0x200a, &arr->pos, 0, &scale, -1);
		set(effect_manager, 3, 0x2008, &arr->pos, 0, 0,-1, 0,-1, 0, 0, 0);

		// joue le son de l'explosion
		se_explode(arr);
		

		mi_memset(&col, 0, sizeof(col));
		mi_memset(&colstat, 0, sizeof(colstat));

		colstat.base.field_0x18 = 0x80395278;// Devrait pas être important, le constructeur n'utilise pas la vtable
		dCcD_GStts_ctor(&colstat.field_0x1c);
		colstat.base.field_0x18 = 0x8037ec20;// bonne vtable
		colstat.field_0x1c.field_0x0 = (void*)0x8037ec40; // une autre vtable...

		dCcD_GObjInf_ctor(&col);
		col.base.field_0x3c = (void*)0x803899d0; // vtable
		col.spheredef.center.x = 0.0f; // devrait pas être utile, vu que c'est pas utilisé avant SetC, mais le jeu fait comme ca...
		col.spheredef.center.y = 0.0f;
		col.spheredef.center.z = 0.0f;
		col.field_0x114 = (void*)0x803899f8; // vtable
		col.field_0x110 = (void*)0x80375cac; // vtable
		col.field_0x128 = (void*)0x80389a4c; // vtable
		col.field_0x12c = (void*)0x8038a1f0; // vtable

		/* TODO: Trouver les arguments qui permettent d'intéragir avec le plus d'objet */
		//Init__9dCcD_SttsFiiP10fopAc_ac_c(&colstat, 0xc8, 0xff, arr);
		Init__9dCcD_SttsFiiP10fopAc_ac_c(&colstat, 0xff, 0xff, arr);
		Set__8dCcD_SphFRC11dCcD_SrcSph(&col, (void*)0x80389e90);
		col.collisionStatus = &colstat;
		//col.base.collMask_a &= ~1;
		col.base.collMask_a |= ~0;
		col.base.onCo |= 1; // active les dommages
		col.base.collisionMode |= 1;

		// rafraichie la position de la sphere
		SetR__8cM3dGSphFf(&col.spheredef, 500);
		SetC__8cM3dGSphFRC4cXyz(&col.spheredef, &arr->pos);

		// active la détéction de collision
		Set__4cCcSFP8cCcD_Obj(collision_manager, &col);
		Set__12dCcMassS_MngFP8cCcD_ObjUc(mass_manager, &col, 3);
		arr = 0;
	}
}

void *threaded_print(void *b) {
	while (1) {
		periodic();
		OSSleepThread(&AudioQueue); // laisse les thread de plus bas niveau s'executer
		OSYieldThread(); // Laisse les thread de même niveau s'executer (peut etre pas nécessaire?)
	}
	return 0;
}

typedef struct event_manager_t event_manager_t;
extern event_manager_t event_manager;

void onNewFile() {
	init__10dSv_save_cFv();
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0280);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0520);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0808);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0901);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0902);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0908);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0A08);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0A20);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0A80);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x0F80);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x1001);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x1610);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x1610);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x1620);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x1801);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x1F02);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x1F40);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2910);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2920);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2A08);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2D01);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2D02);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2D04);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2D08);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2E01);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2E04);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x2F20);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3201);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3304);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3380);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3404);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3440);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3510);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3802);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3840);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3980);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3A20);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x3B02);
	onEventBit__11dSv_event_cFUs(&event_manager, 0x4002);
	/* TODO: Trouver d'autres bits pour refaire fonctioner le lion rouge */

	execItemGet(0x27); // arc
	execItemGet(0xB0); // carquois
	execItemGet(0x12); // fleche

	execItemGet(0x0E); // bombes
	execItemGet(0x31); // 30 bombes

	OSReport("New file inited\n");

	/* TODO: Démarrer le thread au chargement d'une partie */
	// instancie le thread
	// haute priorité et non-joinable
	OSCreateThread(&mt, threaded_print, 0, mts + sizeof(mts), sizeof(mts), 0, 1);
	// démarre le thread
	OSResumeThread(&mt);
}

void mymain() {
	// Enleve la cinematique de début
	*(unsigned*)0x80232C78 = 0x60000000;
	*(unsigned*)0x80232C88 = 0x60000000;
	*(unsigned char*)0x80058BAF = 0;

	/* TODO: modifier le link script pour connaitre le bss et le clear */
	dir = 1;
	arr = 0;

	OSReport("We're in, boys ;)\n");
	//PADInit();
	monkeypatch_close((void*)0x8005D618, (unsigned)onNewFile);

	monkeypatchb_close((void*)0x800d6380, (unsigned)onArrowHit);
	main(0, 0);
}

__attribute__ ((section (".ending")))
void __last(){
}
