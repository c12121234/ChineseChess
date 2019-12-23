#ifndef CONVERTCOORDINATE_H
#define CONVERTCOORDINATE_H


class ConvertCoordinate
{
//This class is for setting ChessCharacter image adjust coordinate.
//mapping ChessBoard coordinate to GraphicsScene coordinate.
//need setting m_nChessImgWidth and m_nChessImgHeigh before use(image's).
public:
    static int ConverX(int x);
    static int ConverY(int y);
    static double m_dRatio;
    static int m_nChessImgWidth;
    static int m_nChessImgHeigh;
private:
    ConvertCoordinate();
};

#endif // CONVERTCOORDINATE_H
