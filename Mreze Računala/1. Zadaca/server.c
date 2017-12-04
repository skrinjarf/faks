#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

void posalji( int sock, char *poruka, int duljinaPoruke )
{
    int poslano = 0; // broj do sada poslanih byte-ova
    int poslanoZadnje; // koliko je poslano u zadnjem send

    while( poslano != duljinaPoruke )
    {
        poslanoZadnje = send(
            sock,
            poruka + poslano,
            duljinaPoruke - poslano,
            0 );

        if( poslanoZadnje == -1 ) { perror( "send" ); break; }
        else poslano += poslanoZadnje;
    }
}

void ucitajUnos( int sock, char *buffer, int bufferSize )
{
    // prima podatke sve dok server ne prekine konekciju
    // problem -- treba osigurati dovoljno veliki buffer...ignoriramo :)

    // recv...
    int primljeno = 0; // koliko smo byte-ova ukupno primili
    int novoprimljeno; // koliko je primljeno u zadnjem recv

    while( 1 )
    {
        novoprimljeno = recv(
            sock,
            buffer + primljeno,
            bufferSize-1 - primljeno,
            0 );

        if( novoprimljeno == -1 ) { perror( "recv" ); break; }
        else if( novoprimljeno == 0 )
        {   printf("UCITANO JE SVE!\n");
            break; // ucitali smo cijeli unos
        }
        else primljeno += novoprimljeno;
    }

    buffer[primljeno] = '\0';
}

void obradiUnos( char *Unos )           //MORAM JOS IZMJENIT
{
    int unutarManje = 0, pocetakItem, krajItem;
    char *temp;
    char povratni[1000];

    if( ( temp = strstr( Unos, "<item" ) ) != NULL )
        pocetakItem = temp - Unos;

    else
        pocetakItem = 0; // ako nema item...ispisuj sve

    if( ( temp = strstr( Unos, "</item>" ) ) != NULL )
        krajItem = temp - Unos;
    else
        krajItem = strlen( Unos ); // ako nema item...ispisuj sve

    int i;
    int j=0; //pozicija u povratnom, inkrement u upisicanju u njega
    for( i = pocetakItem; i < krajItem; ++i )
        if( Unos[i] == '<' )
            unutarManje = 1;
        else if( Unos[i] == '>' )
            unutarManje = 0;
        else if( !unutarManje )   //printf("%c",Unos[i]) ispisuje na ekran uredno
              povratni[j++]=Unos[i];
              povratni[j]='\0'; //zavrsim povratni string

              //sa ovime sam samo izvukao sve unutar <item> i </item>  ali mi treba unutar description i unutar pub date

     for(i=0; i<1000 ; i++) Unos[i]=povratni[i];
}



void obradiKlijenta( int commSocket )
{




    //novi socket za spajanje na server...
        int mojSocket = socket( PF_INET, SOCK_STREAM, 0 );
        if( mojSocket == -1 )
            perror( "socket" );

    //connect...

        struct hostent *hostInfo = gethostbyname( "Net.hr" );  //to bi trebalo spojit na identi.ca
            if( hostInfo == NULL )
            {
                herror( "gethostbyname" );
                printf( "Net.hr!\n");
                exit( 0 );
            }

        struct sockaddr_in adresaServera;

            adresaServera.sin_family = AF_INET;
            adresaServera.sin_port   = htons( 80 );
            adresaServera.sin_addr   = *( (struct in_addr *) hostInfo->h_addr );
            memset( adresaServera.sin_zero, '\0', 8 );

            if( connect(mojSocket,(struct sockaddr *) &adresaServera,sizeof( adresaServera ) ) == -1 )
                   perror( "connect" );

            //ucitavanje sa Net.hr
        char zahtjev[] = "GET /api/statuses/public_timeline.rss HTTP/1.1\nHost: identi.ca\n\n";
        posalji( mojSocket, zahtjev, strlen( zahtjev ) );


        char Unos[20000];
        ucitajUnos(mojSocket,Unos,sizeof(Unos));


        // close...
            if( close( mojSocket ) == -1 )
                perror( "close" );

        //obrada i slanje unosa nazad klijentu
            obradiUnos(Unos);
            posalji(commSocket,Unos,strlen(Unos));  //idem na commsocket jer preko njega komunicram s klijentom
                                                   //idem sa strlen jer je Unos sad puno manji od 20kB pa nemoram sve prebacit

}

int main( int argc, char **argv )
{
    if( argc != 2 )
    {
        printf( "Upotreba: %s port\n", argv[0] );
        exit( 0 );
    }

    // dohvati port iz 1. argumenta komandne linije
    int port;
    sscanf( argv[1], "%d", &port );
    printf( "port=[%d]\n", port );

    // socket...
    int listenerSocket = socket( PF_INET, SOCK_STREAM, 0 );
    if( listenerSocket == -1 )
        perror( "socket" );

    // bind...
    struct sockaddr_in mojaAdresa;

    mojaAdresa.sin_family      = AF_INET;
    mojaAdresa.sin_port        = htons( port );
    mojaAdresa.sin_addr.s_addr = INADDR_ANY;
    memset( mojaAdresa.sin_zero, '\0', 8 );

    if( bind( listenerSocket,
              (struct sockaddr *) &mojaAdresa,
              sizeof( mojaAdresa ) ) == -1 )
        perror( "bind" );

    // listen...
    if( listen( listenerSocket, 10 ) == -1 )
        perror( "listen" );


    while( 1 )
    {
        // accept...
        struct sockaddr_in klijentAdresa;
        int lenAddr = sizeof( klijentAdresa );
        int commSocket = accept( listenerSocket,
                                 (struct sockaddr *) &klijentAdresa,
                                 &lenAddr );

        if( commSocket == -1 )
            perror( "accept" );

        char *dekadskiIP = inet_ntoa( klijentAdresa.sin_addr );
        printf( "Prihvatio konekciju od %s\n", dekadskiIP );

        obradiKlijenta( commSocket );
        close( commSocket );
    }

    return 0;
}
