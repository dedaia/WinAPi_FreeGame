#pragma once
class Physics : public Rect, public Circle
{
public:
    bool IsRectCollision(PlayerChar* play, Rect* rect);
    bool IsRectCollision(Rect* play, Rect* rect);

    void AllCollision(vector<Plant_monster*> pla);

    void plantCollision(vector<Plant_monster*> pla);

    enum COL_DIRECTION // <-���� ���� �ǹ̸� �������� �Ἥ ���߿� �˾ƺ��� ���� ���� ��
    {
        NONE,
        LEFT,
        RIGHT,
        ABOVE,
        BENEATH,
    };

    //���� �ִ� �������� �Ἥ �浹 ������ �� �� �ִ� ������ ������
    COL_DIRECTION GetCollisionDirection(Rect* rect_one, Rect* rect_two)
    {
        //�浹�� �� �簢���� ��ġ�� ������ �ľ��ؼ�,
        // �̵��� �浹 ���°� ������ ����, ���� ������ ������ �Ѵ�

        float _left = rect_one->Left() > rect_two->Left() ? rect_one->Left() : rect_two->Left();
        float _right = rect_one->Right() < rect_two->Right() ? rect_one->Right() : rect_two->Right();
        float _top = rect_one->Top() > rect_two->Top() ? rect_one->Top() : rect_two->Top();
        float _bottom = rect_one->Bottom() < rect_two->Bottom() ? rect_one->Bottom() : rect_two->Bottom();

        //�� ������ ����, �� �簢���� ��ġ�� ���� �� �ִ��� ���� ���� = �������� ���� �� �ִ�

        //�׸��� �������� ����� �Ǻ��ؼ�

        bool collideHorizontal;
        if (_right - _left > _bottom - _top) //���� (����) �簢���� ���ΰ� ���κ��� ũ��
        {
            collideHorizontal = false; // �������� �浹�ߴ� (���Ʒ� ��ġ = �׷��� �������� �����ϴ�)
        }
        else collideHorizontal = true; //���� �浹 (���� ������ ��ġ)

        if (collideHorizontal) //���� �浹�̴�
        {
            //���� ���� ���г��� ���ؼ� �� ���ʿ� �ִ� ���� ����
            if (rect_one->Left() < rect_two->Left())
            {
                return LEFT; //rect_one�� rect_two�� �����̴�
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
                //�浹 ���� ũ�Ⱑ Ŀ�� �ʹ� ũ��! -> �̰� �׳� �����!

                return ABOVE; //��
            }
            else
            {
                return BENEATH; //�Ʒ�
            }
        }
    }

    //�� ����� �ޱ� ���� ���� �߰� (�ɼ�)
    COL_DIRECTION singleDir; //�� ���� ĳ���Ͱ�, �ϳ��� ���ǿ� ���� ������ ���Ⱚ
};