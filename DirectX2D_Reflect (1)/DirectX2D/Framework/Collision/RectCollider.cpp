#include "Framework.h"

RectCollider::RectCollider(Vector2 size) : size(size)
{
    type = Type::RECT;  // ���� ���ϱ� (�簢������)

    Vector2 halfSize = size * 0.5f; // ������ ����� ���� ũ�� �ݿ� ����

    // ����� ���� ũ�⸦ ���� ���������� ���� (�׸��� ���� ��Ͽ� �߰�)
    vertices.emplace_back(-halfSize.x, +halfSize.y);    // ���� +�� ��� �ʿ� ������, ĭ ���߷��� ����
    vertices.emplace_back(+halfSize.x, +halfSize.y);    // ������ ���� ��, �� ���� ������ ��
    vertices.emplace_back(+halfSize.x, -halfSize.y);    // ������ �Ʒ�
    vertices.emplace_back(-halfSize.x, -halfSize.y);    // ���� �Ʒ�
    vertices.emplace_back(-halfSize.x, +halfSize.y);    // ���Ƽ� �ٽ� ���� ��

    vertexBuffer = new VertexBuffer(vertices.data(), sizeof(VertexPos), // VertexPos : �ݶ��̴� ���� ������
        vertices.size());

}

bool RectCollider::IsPointCollision(Vector2 point)
{
    // ������ ���� �ܼ��� �簢���� ���� �ȿ� ������ �׸� (�װ͵� x, y�� ���� �ȴ�)

    // ���� ����

    Matrix invWorld = XMMatrixInverse(nullptr, world);  // '��' ������ ���ʷ� �� �����=������
                                                        // =�ٸ� ������ ���ؼ� �� ������ ��������
    point *= invWorld;                                  // <- �̷���.

    // �̰ɷ� ���� �簢���� �� ������ �����Ѵ�
    // �� ���� �簢���� x, y ���� �ȿ� �ִ����� ���� �׸�

    Vector2 half = Half();

    // ���밪���� ������ point�� ��ǥ��, �簢���� 1��и鿡 ���Դ��� ���
    return ((abs(point.x)) < half.x && abs(point.y) < half.y);

    // -> ����� �������� ���� : �浹ü�� �ڱ� �������� �����ϴ� ��ġ�� �־����� �ʾƼ�
    //                         �ٸ� ���� �浹ü�� ������ �ڱ� ���� ������ �����ϴ� ��ġ�� ������ 0, 0
}

bool RectCollider::IsRectCollision(RectCollider* rect, Vector2* overlap)
{
    if (overlap) // �������� �߻��߰ų�, �̸� �־��� ������(ȣ�� �ܰ迡�� ����Ǹ�)
        return IsAABB(rect, overlap);   // ���簢������ ���ຸ�� ������ ũ�⿡ ���� �Ǻ��� �Ѵ�
    
    // overlap�� ���ٸ�? �������� ���� �� �ְų�, ��� ȣ�� �ܰ迡�� ���� �������� �ʾҴ�
    // -> (���� �簢��������) ���� �簢���̰ų�, �簢���������� �밢�� ��ġ�� ���� �������� ������

    return IsOBB(rect); // OBB �Լ��� �ذ�
}

bool RectCollider::IsCircleCollision(CircleCollider* circle)
{
    // �� �浹�� ���� ��ȸ��.....

    return false;
}

Vector2 RectCollider::LeftTop()
{
    //�������� �ش� : ������ �ƴ϶� ���� ������ ����ؾ� �� ���� �ٱ� ��ǥ

    Vector2 edge = Vector2(-size.x, +size.y) * 0.5f; // �������� ������ �ְ� �ش���
    // edge�� ������ 0, 0�� �ɷ� �Ǿ� �����Ƿ�, �������� �����ϱ� ���� world�� ���ϰ� ��ȯ
    // (�� ���� -> ��¥ ���� ������ ���� �ϸ� �� ����(������ ���, "�� ��ġ")�� �߰�)
    return edge * world;
}

Vector2 RectCollider::LeftBottom()
{
    Vector2 edge = Vector2(-size.x, -size.y) * 0.5f;
    return edge * world;
}

Vector2 RectCollider::RightTop()
{
    Vector2 edge = Vector2(+size.x, +size.y) * 0.5f;
    return edge * world;
}

Vector2 RectCollider::RightBottom()
{
    Vector2 edge = Vector2(+size.x, -size.y) * 0.5f;
    return edge * world;
}

float RectCollider::L() // ��ü ������ �� �ش����� ���� �ִ� �ش��� (�� ���, '���� ���� ��')
{
    // �� ������ ���ؼ� ���� �� �ִ� �ΰ� ���� : �׸��� ���Ʒ��� �������� ������ ã�� �� �ִ�!
    
     // �簢���� �ѷ��� �»� �شܰ� ���� �ش� �߿��� "����"�� �� ����� (x�� ����) ����
    float minLeft = min(LeftTop().x, LeftBottom().x); // min : ������ ��ũ��. �־��� ���ڵ� �� ���� ���� ���� �ǹ�
    
    // ��� �شܰ� ���� �شܵ� ���ؼ� �� ���� ���� ����
    float minRight= min(RightTop().x, RightBottom().x);

    //���� �� �ش� �߿��� �ٽ� �� ����(=�� ������) �ش��� ����
    return min(minLeft, minRight);
}

float RectCollider::R()
{
    // ��, �� �� �شܵ� ���� �Լ��� ����, ��ǥ�� �񱳸� �ٸ���
    float maxLeft = max(LeftTop().x, LeftBottom().x);
    float maxRight = max(RightTop().x, RightBottom().x);
    return max(maxLeft, maxRight);
}

float RectCollider::T()
{
    float maxTop = max(LeftTop().y, LeftBottom().y);
    float maxBottom = max(RightTop().y, RightBottom().y);
    return max(maxTop, maxBottom);
}

float RectCollider::B()
{
    float minTop = min(LeftTop().y, LeftBottom().y);
    float minBottom = min(RightTop().y, RightBottom().y);
    return min(minTop, minBottom);
}

RectCollider::ObbDesc RectCollider::GetObb() // ObbDesc �ڷ����� Ŭ�������� ����ؼ� �Ҽ�����=�����ذ�
{
    // OBB ����ü ������ ����

    obbDesc.position = GlobalPos(); // �ϴ� ��ȯ �߿��� '���'�� ���� -> �ϴ� �� ����
                                    // ���� ��� �� ������ �״�� ���̱⵵ (��� �ʿ��� �� ������ ����)
                                    // Ȥ�� �ʿ��ϸ� �ܺο��� �߰� ������ �ص� �ȴ�

    obbDesc.halfSize = Half();  // ���� ũ��

    obbDesc.axis[0] = Right();  // X��
    obbDesc.axis[1] = Up();     // Y��

    return obbDesc;
}

bool RectCollider::IsAABB(RectCollider* rect, Vector2* overlap)
{
    // �簢������ �ε�ģ ���� ���� �Ǻ�

    Vector2 halfSize = Size() * 0.5f; // ���� ũ�� ���� ����

    // �ε�ģ ������ ������ ����
    float minRight = min(R(), rect->R()); // �� �簢���� �� ��ش� ��, �� ���ʿ� �ִ� ��
    float maxLeft = max(L(), rect->L());  // ��, ��, �� ��� �� �ݴ����� ���� ���ϸ� -> ������ ����
    float minTop = min(T(), rect->T());
    float maxBottom = max(B(), rect->B());

    // �� �������� ũ�⸦ ����
    overlap->x = minRight - maxLeft;
    overlap->y = minTop - maxBottom;

    // �̷��� ���� �����տ� '���� ���̴� ����' �� ũ�Ⱑ ������??
    if (overlap->x > 0 && overlap->y > 0)
        return true;        // ���簢�� ���� �浹�̴�.

    // �׷��� ������ (������� ���� overlap�� �� �� �̻� ũ�Ⱑ 0����)??
    return false;   // ��� ���簢������ �浹�� ��Ȳ�� �ƴϴ�.
}

bool RectCollider::IsOBB(RectCollider* rect)
{
    // �� �Լ��� �����ؾ� �Ǵ� ��Ȳ?
    // 1. ������ ��¥ ���� ��.
    // 2. �簢������ �����ߴµ� (��¼�� �밢���� ��¦ ����������??) ���, ���� ���� ������ ������ X

    // -> "���簢������ �� �ε�ġ�� �������� ���� �� �ƴѵ�, �� �߶� �������� �ָ��� ��Ȳ)

    ObbDesc obbA = GetObb();    // �� �簢���� ���� ������ OBB ����ü�� ���
    ObbDesc obbB = rect->GetObb();

    if (IsSeperate(obbA.axis[0], obbA, obbB)) return false; // ������ �ƴϰ�, ������ ���� �Ű�...
    if (IsSeperate(obbA.axis[1], obbA, obbB)) return false; // �ٸ� �࿡�� �ѹ� �� ��� (�˻�)

    // (�ʼ��� �ƴ�����) ��л� �˻� 2ȸ ��
    if (IsSeperate(obbB.axis[0], obbA, obbB)) return false;
    if (IsSeperate(obbB.axis[1], obbA, obbB)) return false;

    // ������� ���鼭 '�и�'��� ����� �� ���� �� ���Դٸ�???
    // -> ������ �и��� ���� �� �´�. = �浹 ���谡 �ǽɽ�����

    return true;    // �� �� ���� (Ȥ�� "OBB ����� �Ǻ��� ����")
}

bool RectCollider::IsSeperate(Vector2 seperateAxis, ObbDesc box1, ObbDesc box2) // �� �и���
{
    // ������� �������� ���� �׿� ���� �Ÿ� ���� ���踦 ���� (SAT) ...�� �������� ��ġ ���� �ľ�

    // * ���� �Ű������� �޴´�.

    // �Ÿ� ���� (d) : DX�� ���� �Լ�(�� ����ȭ) ���
    float d = abs(Dot(seperateAxis, box1.position - box2.position));

    // Dot (V1, V2) : ���� V1�� ���� V2�� ���� ����� ǥ��
    // abs(f) : �Ű����� f�� ���밪���� �ٲٴ� DX ���� �Լ� �� ���⼭�� ����ȭ
    // * ����� ȣ��� ��ɵ��� �ٸ� �������� ���� �����Ƿ�, �̷� ���� ���� ȣ���� �̸� ���α� ��õ

    // �� �� �и� (x�� �ְ� y�� �����ϱ�) - �ϳ��� ���ؿ� ���� X ����, Y �������� ���

    Vector2 right = box1.axis[0] * box1.halfSize.x; // ���� ������ �࿡ ���� ���� ũ�� �ݿ�
    Vector2 up = box1.axis[1] * box1.halfSize.y; // ���� ����

    //�̿� ���� ù ���ڿ� ������ ���� ������ ����

    float a = abs(Dot(seperateAxis, right)) + abs(Dot(seperateAxis, up));

    // �� ������ ���� 2���� ���� (������ ���� 2������ ������ 1)

    right = box2.axis[0] * box2.halfSize.x;
    up = box2.axis[1] * box2.halfSize.y;

    float b = abs(Dot(seperateAxis, right)) + abs(Dot(seperateAxis, up));

    // �� ������ �����࿡ ���� ���� ����� a, b�� �����Ǿ���
    // �� ����� �Ÿ� d�� ���ؼ� ��ġ���� �ƴ��� ���� �ȴ�

    return d > (a + b); // �� ũ�� "��и����� ����, �� ������ [�и�]�Ǿ���"�� �Ǵ�
}
