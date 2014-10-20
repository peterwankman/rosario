#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef SINE_RETICULUM
#undef CUM_RETICULUM
#endif

#ifdef WIN32
#ifdef CUM_RETICULUM
#include <WinSock2.h>
#else
#include <Windows.h>
#endif

#define dormi(tempus)		Sleep((tempus) * 1000)
#define claude(adiunctio)	closesocket(adiunctio)
#else

#ifdef CUM_RETICULUM
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SOCKET int
#define SOCKADDR struct sockaddr
#define SOCKADDR_IN struct sockaddr_in
#define INVALID_SOCKET -1
#endif

#define dormi(tempus)		sleep(tempus)
#define claude(adiunctio)	close(adiunctio)
#endif

static const char *innomine[] = {
	"In nomine Patris et Filii et Spiritus Sancti. Amen."
}; 

static const char *credo[] = {
	"Credo in deum patrem omnipotentem, creatorem coeli et terrae;",
	"Et in Iesum Christum, filium eius unicum, dominum nostrum,",
	"qui conceptus est de Spiritu sancto, natus ex Maria virgine,",
	"passus sub Pontio Pilato, crucifixus, mortuus et sepultus,",
	"descendit ad inferna, tertia die resurrexit a mortuis,",
	"ascendit ad coelos, sedet ad dexteram dei patris omnipotentis,",
	"inde venturus est iudicare vivos et mortuos;",
	"Credo in Spiritum sanctum,",
	"sanctam ecclesiam catholicam, sanctorum communionem,",
	"remissionem peccatorum,",
	"carnis resurrectionem,",
	"et vitam aeternam. Amen."
};

static const char *gloriapatri[] = {
	"Gloria Patri et Filio et Spiritui Sancto,",
	"sicut erat in principio et nunc et semper et in saecula saeculorum, amen."
};

static const char *paternoster[] = {
	"Pater noster, qui es in caelis,",
	"sanctificetur nomen tuum.",
	"Adveniat regnum tuum.",
	"Fiat voluntas tua, sicut in caelo, et in terra.",
	"Panem nostrum cotidianum da nobis hodie.",
	"Et dimitte nobis debita nostra,",
	"sicut et nos dimittimus debitoribus nostris.",
	"Et ne nos inducas in tentationem,",
	"sed libera nos a malo.",
	"(Quia tuum est regnum et potestas",
	"et gloria in saecula.)",
	"Amen."
};

static const char *avemaria[] = {
	"Ave Maria, gratia plena;",
	"Dominus tecum;",
	"benedicta tu in mulieribus,",
	"et benedictus fructus ventris tui, Iesus.",

	"Sancta Maria, Mater Dei,",
	"ora pro nobis peccatoribus",
	"nunc et in hora mortis nostrae.",
	"Amen."
};

/* In feria secunda et sabbato */
static const char *rosariogaudioso[] = {
	"Qui adaugeat in nobis fidem.",
	"Qui corroboret in nobis spem.",
	"Qui perficiat in nobis caritatem.",

	"Quem, virgo per Spiritum Sanctum, concepisti.",
	"Quem visitando Elisabeth portasti.",
	"Quem, Virgo, genuisti.",
	"Quem in templo praesentasti.",
	"Quem in templo invenisti."
};

/* In feria quinta */
static const char *rosarioluminoso[] = {
	"Qui adaugeat in nobis fidem.",
	"Qui corroboret in nobis spem.",
	"Qui perficiat in nobis caritatem.",

	"Qui apud Iordanem baptizatus est.",
	"Qui ipsum revelavit apud Canense matrimonium.",
	"Qui Regnum Dei annuntiavit.",
	"Qui transfiguratus est.",
	"Qui Eucharistiam instituit."
};

/* In feria tertia et sexta */
static const char *rosariodoloroso[] = {
	"Qui intellectum nostrum illuminet.",
	"Qui voluntatem nostram perficiat.",
	"Qui memoriam nostram roboret.",

	"Qui pro nobis sanguinem sudavit.",
	"Qui pro nobis flagellatus est.",
	"Qui pro nobis spinis coronatus est.",
	"Qui pro nobis crucem baiulavit.",
	"Qui pro nobis crucifixus est."
};

/* In Dominicis et feria quarta */
static const char *rosarioglorioso[] = {
	"Qui cogitationes nostras dirigat.",
	"Qui verba nostra moderetur.",
	"Qui opera nostra gubernet.",

	"Qui resurrexit a mortuis.",
	"Qui in caelum ascendit.",
	"Qui Spiritum Sanctum misit.",
	"Qui te assumpsit.",
	"Qui te in caelis coronavit."
};

static const char *omijesu[] = {
	"O mi Jesu, remitte nobis peccata nostra, custodi nos ab igne inferi, attrahe omnes animas ad caelum praecipue illas maxime egentes misericordiae Tuae."
};

static const char **rosario[7] = {
	rosarioglorioso,
	rosariogaudioso,
	rosariodoloroso,
	rosarioglorioso,
	rosarioluminoso,
	rosariodoloroso,
	rosariogaudioso
};

#if defined CUM_RETICULUM
static SOCKET adiunctio;
#endif

/**/

static int proclama_erratum(const char *sententia) {
	fprintf(stderr, "Annubio vobis luctum magnum: Habemus erratum!\n");
	fprintf(stderr, "%s\n", sententia);
	return EXIT_FAILURE;
}

static int fiat_fenestra(void) {
#if defined WIN32 && defined CUM_RETICULUM
	WSADATA wsa;
	return WSAStartup(MAKEWORD(2,0), &wsa);
#else
	return 0;
#endif
}

#ifdef CUM_RETICULUM
static char* fiat_convivator(void) {
	char *convivator;
	
	if((convivator = malloc(16)) == NULL)
		return NULL;
	
	sprintf(convivator, "%d.%d.%d.%d",
		rand() & 0xff, rand() & 0xff, rand() & 0xff, rand() & 0xff);

	return convivator;
}
#endif

static void dic(const char *sententia) {
#ifdef CUM_RETICULUM
	SOCKADDR_IN addr;
	char *convivator = fiat_convivator();

	if(convivator == NULL) {
		proclama_erratum("Officium fiat_convivator() clamat: NULLUS!");
		return;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(rand() & 0xffff);
	addr.sin_addr.s_addr = inet_addr(convivator);

	free(convivator);

	sendto(adiunctio, sententia, strlen(sententia), 0, (SOCKADDR*)&addr, sizeof(addr));
#endif

	printf("%s\n", sententia);
	dormi(1);	
}

/**/

static void ora(const char **comprecatio, const size_t numerus) {
	size_t n;

	for(n = 0; n < numerus; n++)
		dic(comprecatio[n]);
}

static void ora_avemariam(const size_t numerus, const size_t dies) {
	size_t n;
	const char **rosario_hodiernus = rosario[dies];

	for(n = 0; n < 4; n++)
		dic(avemaria[n]);
	dic(rosario_hodiernus[numerus]);
	for(n = 4; n < 8; n++)
		dic(avemaria[n]);
}

int main(void) {
	time_t nunc;
	int dies, i, j;

#ifdef CUM_RETICULUM
	if(fiat_fenestra()) {
		proclama_erratum("Officium fiat_fenestra() clamat: Mortuus sum.");
		return EXIT_FAILURE;
	}

	adiunctio = socket(AF_INET, SOCK_DGRAM, 0);
	if(adiunctio == INVALID_SOCKET) {
		proclama_erratum("Officium socket() clamat: Adiunctio invalidum est.");
		return EXIT_FAILURE;
	}
#endif

	nunc = time(NULL);
	dies = localtime(&nunc)->tm_wday;
	srand(nunc);

	ora(innomine, 1);
	ora(credo, 12);

	ora(gloriapatri, 2);
	ora(paternoster, 12);

	ora_avemariam(0, dies);
	ora_avemariam(1, dies);
	ora_avemariam(2, dies);

	for(i = 0; i < 5; i++) {
		ora(gloriapatri, 2);
		ora(paternoster, 12);
		for(j = 0; j < 10; j++)
			ora_avemariam(i + 3, dies);
	}

	ora(gloriapatri, 2);
	ora(omijesu, 1);

#ifdef CUM_RETICULUM
	claude(adiunctio);
#ifdef WIN32
	WSACleanup();
#endif
#endif

	return EXIT_SUCCESS;
}

