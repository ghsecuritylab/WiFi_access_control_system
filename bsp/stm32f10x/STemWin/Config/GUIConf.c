#include "GUI.h"
#include <rtthread.h>


#define USE_EXRAM  0//ʹ���ڲ�RAM
//����EMWIN�ڴ��С
#define GUI_NUMBYTES  (1000*1024)
#define GUI_BLOCKSIZE 256  //���С


//GUI_X_Config
//��ʼ����ʱ�����,��������emwin��ʹ�õ��ڴ�
void GUI_X_Config(void) {
//	if(USE_EXRAM) //ʹ���ⲿRAM
//	{
//		U32 *aMemory = rt_malloc(SRAMEX,GUI_NUMBYTES); //���ⲿSRAM�з���GUI_NUMBYTES�ֽڵ��ڴ�
//		GUI_ALLOC_AssignMemory((void*)aMemory, GUI_NUMBYTES); //Ϊ�洢����ϵͳ����һ���洢��
//		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //���ô洢���ƽ���ߴ�,����Խ��,���õĴ洢������Խ��
//		GUI_SetDefaultFont(GUI_FONT_6X8); //����Ĭ������
//	}else  //ʹ���ڲ�RAM
//	{
//		U32 *aMemory = rt_malloc(SRAMIN,GUI_NUMBYTES); //���ڲ�RAM�з���GUI_NUMBYTES�ֽڵ��ڴ�
		U32 *aMemory = rt_malloc(GUI_NUMBYTES); //���ڲ�RAM�з���GUI_NUMBYTES�ֽڵ��ڴ�
		GUI_ALLOC_AssignMemory((U32 *)aMemory, GUI_NUMBYTES); //Ϊ�洢����ϵͳ����һ���洢��
		GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //���ô洢���ƽ���ߴ�,����Խ��,���õĴ洢������Խ��
		GUI_SetDefaultFont(GUI_FONT_6X8); //����Ĭ������
//	}
}