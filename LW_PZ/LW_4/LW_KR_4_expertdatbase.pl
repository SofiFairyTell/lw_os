:-op(100,xfx,[���,������_��,����]).
:-dynamic ���/2.
:-dynamic ������_��/2.
:-dynamic ����/2.

%���� ������
������� ��� ��������:-������� ��� ���_�������, ������� ������_�� �������.
������� ��� ��������:-������� ��� ���_�������, ������� ������_�� ��������.
������� ��� ���_�������:-������� ���� ������, ������� ���� ��������.
%������� ������
������ ���� ������.
������ ���� ��������.
������ ������_�� ��������.
%��������� ��������� ��������� ����������
%��� ������� ���� ������� "���" ��������� ����������� ���������
���������(true,'���� � ���������'):-!.
���������((A,B),(P1,P2)):-!,���������(A,P1),���������(B,P2).
���������((A;B),(P1;P2)):-!,���������(A,P1),���������(B,P2).
���������((A,(B;C)),(P1,P2;P3)):-!,���������(A,P1),(���������(B,P2);���������(C,P3)).
���������(A,������_���(A,P1)):-clause(A,����),���������(����,P1).
