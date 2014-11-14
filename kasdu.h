
#ifndef KASDU
#define KASDU

#define PACKET_TIME_SIZE        4
#define ADDR3D_NETWORK_SIZE     4
#define ADDR3D_NODE_SIZE        6

struct Address3D {

    unsigned char Network[ADDR3D_NETWORK_SIZE];		// номер сети
    unsigned char Node[ADDR3D_NODE_SIZE];		// номер сетевого адаптера
    unsigned short Socket;				// номер сокета
};

struct PacketHead {

    short n; 				/* для выравнивания - у Юры этого нет */
    struct Address3D To, From;		/* 01.03.99   тут будет адрес ~10байт */
    short Number;			/* Номер посылаемого пакета           */
    short Length;			/* Длина посылаемого пакета 1+s+1+4+84*3=258+s */
    char  t[ PACKET_TIME_SIZE];		/* Время регистрации  посылаемого пакета (секунды с 01.01.70) */
    short Dest;				/* Направление передачи:   0=сеть, 1=модем */
    short PakLen;			/* Длина блоков 500                   */
    short CurNum;			/* Текущий номер блока 0              */
    short NumPieces;			/* Количество поступивших блоков1     */
    char key;				/* ключ потока - 1б - для ТУ всегда 2*/
};

#endif
