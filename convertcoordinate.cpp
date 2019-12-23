#include "convertcoordinate.h"

double ConvertCoordinate::m_dRatio = 1.0;
int ConvertCoordinate::m_nChessImgWidth = 0;
int ConvertCoordinate::m_nChessImgHeigh = 0;
int ConvertCoordinate::ConverX(int x)
{
    return 40+x*60-(m_dRatio*m_nChessImgWidth/2);
}

int ConvertCoordinate::ConverY(int y)
{
    return 39+y*60-(m_dRatio*m_nChessImgHeigh/2);
}

ConvertCoordinate::ConvertCoordinate()
{

}
