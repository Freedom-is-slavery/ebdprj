/**
 * @file 数码管显示
 * @note 型号：LG3641BH，四位七段共阳极，阳极加330欧姆电阻使用
 * 
 **/

#include "main.h"
#include "digit.h"

/* 定义每一位数码管显示时点亮的位段,依次为a,b,c,d,e,f,g,dp */
/* 由于没有小数部分,DP段全部置1保持常灭*/
uint8_t DigTbl[10][8] =
{
	{0, 0, 0, 0, 0, 0, 1, 1},			//0
	{1, 0, 0, 1, 1, 1, 1, 1},			//1
	{0, 0, 1, 0, 0, 1, 0, 1},			//2
	{0, 0, 0, 0, 1, 1, 0, 1},			//3
	{1, 0, 0, 1, 1, 0, 0, 1},			//4
	{0, 1, 0, 0, 1, 0, 0, 1},			//5
	{0, 1, 0, 0, 0, 0, 0, 1},			//6
	{0, 0, 0, 1, 1, 1, 1, 1},			//7
	{0, 0, 0, 0, 0, 0, 0, 1},			//8
	{0, 0, 0, 0, 1, 0, 0, 1}			//9
};


/**
 * @brief 选通特定一位数码管
 * @param dig 
 * @arg DIG1, DIG2, DIG3, DIG4代表从左至右位
 * 
 */
void DigitChoice(uint8_t endig)
{
    uint8_t digarr[4] = {RESET, RESET, RESET, RESET};
    digarr[endig - 1] = SET;

    HAL_GPIO_WritePin(DIG1_GPIO_Port, DIG1_Pin, digarr[0]);
    HAL_GPIO_WritePin(DIG2_GPIO_Port, DIG2_Pin, digarr[1]);
    HAL_GPIO_WritePin(DIG3_GPIO_Port, DIG3_Pin, digarr[2]);
    HAL_GPIO_WritePin(DIG4_GPIO_Port, DIG4_Pin, digarr[3]);
}

/**
 * @brief 显示特定一位数码管的数字
 * @param dig
 * @arg DIG1, DIG2, DIG3, DIG4代表从左至右位
 * @param num 
 * @arg 0, 1, ... , 9
 * 
 */
void DisplayOneDigit(uint8_t dig, uint8_t num)
{
    DigitChoice(dig);

    HAL_GPIO_WritePin(SEG_A_GPIO_Port, SEG_A_Pin, DigTbl[num][0]);
    HAL_GPIO_WritePin(SEG_B_GPIO_Port, SEG_B_Pin, DigTbl[num][1]);
    HAL_GPIO_WritePin(SEG_C_GPIO_Port, SEG_C_Pin, DigTbl[num][2]);
    HAL_GPIO_WritePin(SEG_D_GPIO_Port, SEG_D_Pin, DigTbl[num][3]);
    HAL_GPIO_WritePin(SEG_E_GPIO_Port, SEG_E_Pin, DigTbl[num][4]);
    HAL_GPIO_WritePin(SEG_F_GPIO_Port, SEG_F_Pin, DigTbl[num][5]);
    HAL_GPIO_WritePin(SEG_G_GPIO_Port, SEG_G_Pin, DigTbl[num][6]);
    HAL_GPIO_WritePin(SEG_DP_GPIO_Port, SEG_DP_Pin, DigTbl[num][7]);

}