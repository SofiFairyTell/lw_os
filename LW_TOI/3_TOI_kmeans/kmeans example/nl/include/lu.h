#ifndef __LU_H__
#define __LU_H__

/**
  \file
  \f$LU\f$-����������.

  ���� �������� �������, ����������� � ������������ \f$LU\f$-����������
  ���������� �������.

  ������������ ���������� ������� \f$A\f$ ������� \f$n\f$ ��������� ����������
  ���� \f$PA=LU\f$, ��� \f$P\f$ - ������� ������������, \f$L\f$ -
  ���������������� ������� � ��������� ����������, \f$U\f$ -
  ����������������� �������. ����� ���������� ���������� ��� ������� ������
  �������� ��������� \f$Ax=b\f$, ������� ������ ������� �� ���� ������
  \f$Ly=Pb\f$ � \f$Ux=y\f$.
*/

/**
  \example xlu.c
*/

/**
  \f$LU\f$-���������� �������.

  ������� ������� \f$LU\f$-���������� � ������ ����� ��������������� ����������
  ������� \f$A\f$ ������� \f$n\f$. �� ������ ��������� � ����������������� �����
  ������� \f$A\f$ �������� �������� ������� \f$U\f$. ���������������� ����� ������� \f$A\f$
  �������� ��������������� �������� ������� \f$L\f$. ������������ ��������
  ������� \f$L\f$ ����� \f$1\f$. ������� ������������ \f$P\f$ ������������ ��������
  ������������ \f$p\f$, � ������� \f$p[j]\f$ - ������ ������� ������ �� \f$j\f$-�� ��������. ��
  ������ \f$sgn\f$ - ������������ ������� \f$P\f$. ������� ���������� ������ ������ ����� ���������������
  ������� \f$A\f$ ������� \f$n\f$. ��� �������, ������ ������ ���������� �� ����������
  ����� ��������������� �� ����� ��� � \f$10\f$ ���.
  
  ��� ���������� ������������ �������� ������ � ������� �������� ��������
  �� �������. ��� ������ ����� ��������������� ������������ ��������,
  ��������� � [FMM, KMN].
  
  ������������: \f$\frac{2}{3}n^3 + O(n^2)\f$ �������� � ��������� �������
*/
extern double lu_decomp(double** A, size_t n, size_t* p, int *sgn);


/**
  ������� ������� �������� ���������.

  ������� ������� ������� ���������� ������� �������� ��������� \f$Ax=b\f$
  ������� \f$n\f$, ��������� �������������� ��������� \f$LU\f$-���������� ������� \f$A\f$,
  �������������� �������� \f$LU\f$ � �������� ������������ \f$p\f$, �������������
  �������� #lu_decomp. ������� \f$x\f$ ������������ �� ����� ������� ������ �����
  \f$b\f$. ������� \f$LU\f$ � ������ \f$p\f$ �� �������� ������ �������� � ����� ����
  ������������ ��� ������� ������� � ������ ������ ������.

  ������������ �������� ������ � �������� �����������.
  
  ������������: \f$2n^2 + O(n)\f$ �������� � ��������� �������
*/

/**
  ������� ������� �������� ���������.

  ������� ������� ������� ���������� ������� �������� ��������� \f$Ax=b\f$ ������� \f$n\f$,
  ��������� �������������� ��������� \f$LU\f$-���������� ������� \f$A\f$, ��������������
  �������� \f$LU\f$ � �������� ������������ \f$p\f$, ������������� �������� #lu_decomp.
  ������� \f$x\f$ ������������ �� ����� ������� ������ ����� \f$b\f$.
  ������� \f$L\f$U � ������ \f$p\f$ �� �������� ������ �������� � ����� ���� ������������ ���
  ������� ������� � ������ ������ ������.

  ������������ �������� ������ � �������� �����������.
  
  ������������: \f$2n^2 + O(n)\f$ �������� � ��������� �������
*/
extern void lu_solve(double** LU, size_t n, size_t* p, double* b);

/**
  ���� ��� ������������� ��������� ������� ������� �������� ���������.

  ������� ��������� ���� ��� ������������� ��������� ������� \f$x\f$ ������� �������� 
  ��������� \f$Ax=b\f$. ������������ �������������� ��������� \f$LU\f$-���������� ������� \f$A\f$, 
  �������������� �������� \f$LU\f$ � �������� ������������ \f$p\f$, ������������� �������� #lu_decomp.
  ������������ ���������� ������� \f$x\f$ � ������ ������� \f$r=Ax-b\f$.

  ������������ ��������� ��������: ������� ����������� ������ \f$r'=Ax-b\f$,
  ����� ����� � ������� ������� #lu_solve �������� ������� \f$Ar'=b\f$ �, �������,
  ������������ ���������� ������� \f$x=x-r\f$ � ������ ������� \f$Ax-b\f$.
 
  ������������: \f$2n^2 + O(n)\f$ �������� � ��������� �������
*/
extern void lu_improve(double** LU, size_t n, size_t* p, double* b, double* x, double* r);

/**
  ������������ �������.

  ������� ���������� ������������ ���������� ������� \f$A\f$ ������� \f$n\f$. ������������� 
  �������������� ��������� \f$LU\f$-���������� ������� A, �������������� �������� \f$LU\f$ � 
  ������������� \f$sgn\f$ ������� ������������ \f$P\f$ (��� ������ ������������ �� �����), 
  ������������� �������� #lu_decomp.

  ������������: \f$2n + O(1)\f$ �������� � ��������� �������
*/
extern double lu_det(double** LU, size_t n, int sgn);

/**
  ��������� �������.

  ������� ������� ������� \f$B\f$, �������� � ������� \f$A\f$. ������������ �������������� 
  ��������� \f$LU\f$-���������� ������� \f$A\f$, �������������� �������� \f$LU\f$ � �������� 
  ������������ \f$p\f$, ������������� �������� #lu_decomp.

  ������������: \f$2n^2 + O(n)\f$ �������� � ��������� �������
*/
extern void lu_invert(double** LU, size_t n, size_t* p, double** B);


/**
  ��������� ������� \f$A\f$, �������������� ��������� \f$LU\f$ � \f$p\f$, �� ������ \f$v\f$. 

  ������� ������� ������������ \f$A\cdot v\f$.
  ������������ �������������� 
  ��������� \f$LU\f$-���������� ������� \f$A\f$, �������������� �������� \f$LU\f$ � �������� 
  ������������ \f$p\f$, ������������� �������� #lu_decomp. ��������� ������������
  � ������� \f$res\f$.

  ������������: \f$2n^2 + O(n)\f$ �������� � ��������� �������
*/
extern void lu_mult_col(double** LU, size_t n, size_t* p, double* v, double* res);

#endif
