#ifndef __RETARGET_H
#define __RETARGET_H
#pragma import(__use_no_semihosting)
void _sys_exit(int x)
{
    x = x;
}
struct __FILE
{
    int handle;
};
FILE __stdout;
int fputc(int ch, FILE *f)
{
    USART_SendData(USART1, (unsigned char) ch);
    while (!(USART1->SR & USART_FLAG_TXE));
    return (ch);
}
#endif







