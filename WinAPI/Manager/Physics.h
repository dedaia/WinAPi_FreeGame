#pragma once
class Physics : public Rect, public Circle
{
public:
    bool IsRectCollision(PlayerChar* play, Rect* rect);
    bool IsRectCollision(Rect* play, Rect* rect);

    void AllCollision(vector<Plant_monster*> pla);

    void plantCollision(vector<Plant_monster*> pla);

    enum COL_DIRECTION // <-위와 같은 의미를 열거형을 써서 나중에 알아보기 쉽게 만든 것
    {
        NONE,
        LEFT,
        RIGHT,
        ABOVE,
        BENEATH,
    };

    //위에 있는 열거형을 써서 충돌 방향을 알 수 있는 연산을 만들자
    COL_DIRECTION GetCollisionDirection(Rect* rect_one, Rect* rect_two)
    {
        //충돌한 두 사각형의 겹치는 영역을 파악해서,
        // 이들의 충돌 형태가 수직에 가까운가, 수평에 가까운가를 보고자 한다

        float _left = rect_one->Left() > rect_two->Left() ? rect_one->Left() : rect_two->Left();
        float _right = rect_one->Right() < rect_two->Right() ? rect_one->Right() : rect_two->Right();
        float _top = rect_one->Top() > rect_two->Top() ? rect_one->Top() : rect_two->Top();
        float _bottom = rect_one->Bottom() < rect_two->Bottom() ? rect_one->Bottom() : rect_two->Bottom();

        //위 연산을 통해, 두 사각형의 겹치는 영역 중 최대한 작은 영역 = 교집합을 구할 수 있다

        //그리고 교집합의 모양을 판별해서

        bool collideHorizontal;
        if (_right - _left > _bottom - _top) //작은 (가상) 사각형의 가로가 세로보다 크면
        {
            collideHorizontal = false; // 수직으로 충돌했다 (위아래 위치 = 그래서 교집합이 납작하다)
        }
        else collideHorizontal = true; //수평 충돌 (왼쪽 오른쪽 위치)

        if (collideHorizontal) //수평 충돌이다
        {
            //서로 왼쪽 선분끼리 비교해서 더 왼쪽에 있는 쪽이 왼쪽
            if (rect_one->Left() < rect_two->Left())
            {
                return LEFT; //rect_one은 rect_two의 왼쪽이다
            }
            else
            {
                return RIGHT;
            }
        }
        else
        {
            if (rect_one->Bottom() < rect_two->Bottom())
            {
                if (_bottom - _top > 10) return NONE;
                //충돌 영역 크기가 커도 너무 크다! -> 이건 그냥 통과다!

                return ABOVE; //위
            }
            else
            {
                return BENEATH; //아래
            }
        }
    }

    //위 결과를 받기 위한 변수 추가 (옵션)
    COL_DIRECTION singleDir; //한 명의 캐릭터가, 하나의 물건에 대해 가지는 방향값
};