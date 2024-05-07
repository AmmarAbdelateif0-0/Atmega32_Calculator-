/*
 * CLCD_Interface.h
 *
 *  Created on: Apr 23, 2024
 *      Author: aboam
 */

#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_

ES_t CLCD_EnuSendCommand(u8 copy_u8Command);


ES_t CLCD_EnuSendData(u8 copy_u8Data);

ES_t CLCD_EnuInit(void);

ES_t CLCD_EnuSendString(const char* Copy_PCstring);

ES_t CLCD_EnuGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);

ES_t CLCD_EnuClearDisplay(void);

ES_t CLCD_EnuWriteNumber(f64 Copy_u8Number);

ES_t CLCD_EnuWriteSpeacialCharacter(u8* Copy_pu8Pattern ,u8 Copy_u8PatternNumber ,u8 Copy_u8XPos ,u8 Copy_u8YPos);
#endif /* CLCD_INTERFACE_H_ */
