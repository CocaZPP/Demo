#ifndef _FONT14X14_H_
#define _FONT14X14_H_

extern uint8  GUI_PutHZ14x14(uint8 x, uint8 y, uint16 hz_code);
extern uint8 GUI_PutStringConst14x14(uint8 x, uint8 y, uint8 const *buf);
extern uint8 GUI_PutString14x14(uint8 x, uint8 y, uint8 *buf);
extern uint8 GUI_PutStringConst14x14_7x14(uint8 x, uint8 y, uint8 const *buf);

extern uint8 Get_TxtLength14x14(uint8 const *buf);


#endif
