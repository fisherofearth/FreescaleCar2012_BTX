#include "image.h"

/*
 * ��ƽ����
 * Average of value-value
 */
#define	Average(v1,v2) 	((v1 + v2) / 2)

/*
 * ���ݶ�
 * Gradient of value-value
 */
#define Gradient(v1,v2)	(v1 - v2)

/*
 * �����ֵ
 */
#define	ABS(x) 			((x)<0?-(x):(x))

/*
 * ��㵽ֱ�ߵľ���
 * Distance of point-LINE
 * ����k��bӦΪ��ֵ��10��
 * ���ؽ��Ϊ��ֵ��10��
 */
int DPL(struct POINT P, struct LINE L)
{
	return (((L.k * P.x)) - (P.z*10) + L.b);
}

/*
 * ��������м��
 * midPOINT of POINT-POINT
 */
struct POINT MPP(struct POINT P1, struct POINT P2) {
	struct POINT tmp;
	tmp.x = Average(P1.x , P2.x);
	tmp.z = Average(P1.z , P2.z);
	return tmp;
}

/*
 * ����������ֱ��
 * LINE of POINT-POINT
 * ����k��bΪ��ֵ��10��
 */
struct LINE LPP(struct POINT P1, struct POINT P2)
{
	struct LINE tmp;
	//if(P1.x == P2.x)P1.x++;
	tmp.k = ((ABS(P1.z - P2.z))*10)/(P1.x-P2.x);
	tmp.b = (P1.z*10) - ((P1.x*(ABS(P1.z - P2.z))*10)/(P1.x-P2.x));
	return tmp;
}


/*
 * ������������б�̶�
 * P1 - P2
 */
int KPP(struct POINT P1, struct POINT P2)
{
	//if(P1.z == P2.z)P1.z ++;
	return (((P1.x-P2.x)*10) / (ABS(P1.z - P2.z)));
}
