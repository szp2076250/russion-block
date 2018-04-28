
#include "stdafx.h"
#include "russion block.h"
#include "Russion1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Russion::Russion()
{

}

Russion::~Russion()
{

}

void Russion::DrawBackground(CDC * pdc)
{
	CDC dcm;
	dcm.CreateCompatibleDC(pdc);
	dcm.SelectObject(&mBackGround);
	pdc->BitBlt(0,0,400,600,&dcm,0,0,SRCCOPY);
}

void Russion::Clear(CDC *pDC)
{
	CDC dcm;
	dcm.CreateCompatibleDC(pDC);
	dcm.SelectObject(&mBlockBitmap);

	//400*500;
	for (int i = 0; i <= 40; i++)
	{
		for (int j = 0; j <= 50; j++)
		{
			pDC->StretchBlt(0 + 10 * i, 10 * j, 10, 10, &dcm, 0, 0, 48, 48, SRCCOPY);
		}
	}
}

void Russion::IniBlock()
{
	mBlockGreen.LoadBitmap(IDB_GREEN);
	mBlockRed.LoadBitmap(IDB_RED);
	mBlockPing.LoadBitmap(IDB_PING);
	mBlockBlue.LoadBitmap(IDB_BLUE);
	mBackGround.LoadBitmap(IDB_BACKGROUND);
	mBlockBitmap.LoadBitmap(IDB_GE);
	
	mCanMove = false; //���ƶ�
	mGameStart = false;
	mGamePause = false;
	mAdvanceVersion = false;
	m_IsCreat = false;
	mGameStop = false;
	mRotateBlock = false;   
	mSpeed = 4;  

	mRow = 20;   //20��26��
	mCol = 26;

	mLeftTopPoint.x = 0;     //���鿪ʼ���������
	mLeftTopPoint.y = 19/2;    //���鿪ʼ���������

	ZeroBackGround();   //�������������
	GetABlock();
}

//�������������
//�ж��Ƿ��Ǹ߼��� �߼��汾���(1-9) �Ͱ汾���(1-6)
//��շ������顣ָ����Ӧ�ķ��������ĸ�λ����Ҫ���� ����Ϊ1
void Russion::GetABlock()
{
	if(mGameStop) return;  

	srand(GetTickCount());
	iKindOfBlocks = rand() % 6;
	if (mAdvanceVersion) iKindOfBlocks = rand() % 9;

	switch(iKindOfBlocks)
	{
	case 1:              
		mOldBlock[0][0] = 1;
		mOldBlock[1][0] = 1;
		mOldBlock[2][0] = 1;
		mOldBlock[3][0] = 1;
		break;
	case 2:
		mOldBlock[1][0] = 1;
		mOldBlock[0][0] = 1;
		mOldBlock[0][1] = 1;			
		mOldBlock[2][0] = 1;
		break;
	case 3:
		mOldBlock[0][0] = 1;
		mOldBlock[0][1] = 1;
		mOldBlock[1][0] = 1;
		mOldBlock[1][1] = 1;
		break;
	case 4:
		mOldBlock[0][1] = 1;
		mOldBlock[1][0] = 1;
		mOldBlock[1][1] = 1;
		mOldBlock[1][2] = 1;
		break;
	case 5:
		mOldBlock[0][1] = 1;
		mOldBlock[1][0] = 1;
		mOldBlock[2][0] = 1;
		mOldBlock[1][1] = 1;
		break;
	case 6:
		mOldBlock[0][0] = 1;
		mOldBlock[1][0] = 1;
		mOldBlock[1][1] = 1;
		mOldBlock[2][1] = 1;
		break;
	case 7:              //��չ
		mOldBlock[0][0] = 1;
		mOldBlock[0][1] = 1;
		mOldBlock[0][2] = 1;
		mOldBlock[1][2] = 1;
		mOldBlock[2][2] = 1;
	case 8:
		mOldBlock[0][0] = 1;
		mOldBlock[1][1] = 1;
		mOldBlock[2][2] = 1;
	case 9:
		mOldBlock[0][0] = 1;
		mOldBlock[0][2] = 1;
		mOldBlock[1][1] = 1;
		mOldBlock[2][0] = 1;
		mOldBlock[2][2] = 1;
	default:
		mOldBlock[0][0] = 1;
		mOldBlock[0][1] = 1;
		mOldBlock[1][1] = 1;
		mOldBlock[2][1] = 1;
		break;
	}
}

void Russion::ClearBlock(block S)
{
	for(int i = 0;i<4;i++)
	{
		for(int j = 0;j<4;j++)
		{
			S[i][j]=0;
		}
	}
}

//���ݷ���direct �ƶ�����
//1������ 2������ 3������ default������ 
//�����ϵĻ����� RotateBlock ��ת���� 
//��������ң�
//          ����ڿ����ƶ�(���ᳬ������ı߽粢�Һͱ�ķ���û����ײ)������£����ƶ�
void Russion::MoveBlocks(int direct)  
{
	int i =0;
	int j =0;

	switch(direct)
	{
	case 1:
		RotateBlock();
		break;
	case 2:
		if(CanNotDown()==true)
		{
		mLeftTopPoint.x++;
		}
		break;
	case 3:
		if(mLeftTopPoint.y>0 && LeftAndRight()==true)
		{
		mLeftTopPoint.y--;
		}
		else
		{
		}
		break;
	default: 

		for(i=0;i<=3;i++)
		{
			for(j=0;j<=3;j++)
			{
				if(mOldBlock[i][j]==1)
				{
					if(mLeftTopPoint.y+j>17)
						return;
				}
			}
		}

		if(LeftAndRight()==false)
		{
			break;
		}
		else
		{
			mLeftTopPoint.y++;
		}
	}
}

void Russion::DrawBlock(CDC *pDC)
{
	CDC dcm;   //����DC
	dcm.CreateCompatibleDC(pDC);
	dcm.SelectObject(&mBlockBlue);

	int i;
	int j;

	ZeroBackGround();

	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			if(mOldBlock[i][j]==1)
			{
				pDC->StretchBlt(mLeftTopPoint.x+i*20,mLeftTopPoint.y+j*20,20,20,&dcm,0,0,48,48,SRCCOPY);
			}
		}
	}

	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			mAfterBlock[i][j] = mOldBlock[i][j];
		}
	}

}

void Russion::ClearWill(CDC *pDC)
{
	CDC dcm;  
	dcm.CreateCompatibleDC(pDC);
	dcm.SelectObject(&mBlockBitmap);	
	for(int i=0;i<=3;i++)
	{
		for(int j=0;j<=3;j++)
		{
	
		pDC->StretchBlt(mLeftTopPoint.x+i*20,mLeftTopPoint.y+j*20,20,20,&dcm,0,0,48,48,SRCCOPY);

		}
	}
}

void Russion::ZeroBackGround()
{
	for(int i=0;i<=mCol;i++)
		for(int j=0;j<=mRow;j++)
			game[i][j] = 0 ; //ȫ��Ϊ��
}

//���������������� ������������ֵΪ0 ���ǰ�ɫ��
// ������������ֵΪ1 �ͻ��Ʒ��顣
// Ȼ���֮ǰ���ƵĲ�����׼���´λ���
void Russion::UpdateBackGround(CDC *pDC)
{
	Change();
	CDC dcm;
	dcm.CreateCompatibleDC(pDC);
	
	for(int i=0;i<=mCol;i++)
	{
		for(int j=0;j<=mRow;j++)
		{

			if(game[i][j]==0)
			{
			dcm.SelectObject(&mBlockBitmap);
			pDC->StretchBlt(0+20*j,0+20*i,20,20,&dcm,0,0,48,48,SRCCOPY);
			}

			if(game[i][j]==1)
			{
			dcm.SelectObject(&mBlockBlue);
			pDC->StretchBlt(0+20*j,0+20*i,20,20,&dcm,0,0,48,48,SRCCOPY);
			}
		
		}
	}

	for(int i=0;i<=3;i++)
	{
		for(int j=0;j<=3;j++)
		{
			mAfterBlock[i][j] =  mOldBlock[i][j];
		}
	}

	if(CanNotDown()==true)
	{
		ClearBefore();
	}
	
}	

//������������Ӧ��λ����1  
//֮���������ֵΪ1��Ԫ�ء�
void Russion::Change()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(mOldBlock[i][j]==1)
				game[i+mLeftTopPoint.x][j+mLeftTopPoint.y]=1;
}

//����������ֵ��֮ǰ���Ƶ�λ�����
void Russion::ClearBefore()
{
	for(int i=0;i<=3;i++)
		for(int j=0;j<=3;j++)
			if(mAfterBlock[i][j]==1)
				game[i+mLeftTopPoint.x][j+mLeftTopPoint.y]=0;

}

//�������з����ʱ�����ƶ�
bool Russion::LeftAndRight()
{
	for(int i=0;i<=3;i++) 
	{
		for(int j=0;j<=3;j++)
		{
			if(mOldBlock[i][j]==1 && mOldBlock[i][j+1]==0)
			{
				if(game[mLeftTopPoint.x+i][mLeftTopPoint.y+j+1]==1)
				{
					return false;
				}
			}

				if(mOldBlock[i][j]==1 && mOldBlock[i][j-1]==0)
			{
				if(game[mLeftTopPoint.x+i][mLeftTopPoint.y+j-1]==1)
				{
					return false;
				}
			}
		}
	}

	return true;
}

//�ж��Ƿ��Ѿ���������ķ�����ײ���ߺͱ߽���ײ��
//�����ж����Ƿ񳬳��߽�
//Ȼ���ܳ����Ѿ����ڵ����淽��
//���������һ���Ƿ�ͱ��������ͻ
bool Russion::CanNotDown()
{	

	//���ܳ���������
	int i,j;

	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{
			if(mOldBlock[i][j]==1)
			{
				if(i+mLeftTopPoint.x>=mCol||j+mLeftTopPoint.y>=mRow)
				{
					return false;
				}
			}
		}
	}


	//���ܳ����������Ѿ����ڵķ���
	if(BlockWidthLength()==3)
	{
		for (j = 0; j <= 3; j++)
		{
			if (mOldBlock[3][j] == 1)
			{
				if (game[mLeftTopPoint.x + 4][mLeftTopPoint.y + j] == 1)
				{
					return false;
				}
			}
		}
	}
	
	if(BlockWidthLength()==2)
	{
		for (j = 0; j <= 3; j++)
		{
			if (mOldBlock[2][j] == 1)
			{
				if (game[mLeftTopPoint.x + 3][mLeftTopPoint.y + j] == 1)
				{
					return false;
				}
			}
		}
	}

	if(BlockWidthLength()==1)
	{
		for (j = 0; j <= 3; j++)
		{
			if (mOldBlock[1][j] == 1)
			{
				if (game[mLeftTopPoint.x + 2][mLeftTopPoint.y + j] == 1)
				{
					return false;
				}
			}
		}
	}

	if(BlockWidthLength()==0)
	{
		for (j = 0; j <= 3; j++)
		{
			if (mOldBlock[0][j] == 1)
			{
				if (game[mLeftTopPoint.x + 1][mLeftTopPoint.y + j] == 1)
				{
					return false;
				}
			}
		}
	}

	for(i=0;i<=3;i++)     
	{
		for(j=0;j<=3;j++)
		{
			if(mOldBlock[i+1][j]==0 && mOldBlock[i][j]==1)
			{
				if (game[mLeftTopPoint.x + i + 1][mLeftTopPoint.y + j] == 1)
				{
					return false;
				}
			}
		}
	}

	return true;
}

//��������
int Russion::BlockWidthLength()
{
	for(int i=3;i>=0;i--)
		for (int j = 0; j <= 3; j++)
			if(mOldBlock[i][j]==1)
				return i;
	return -1;
}

int Russion::BlockHeightLength()
{
	int i,j;
	for(j=3;j>=0;i--)
		for(i=0;i<=3;i++)
			if(mOldBlock[i][j]==1)
				return j;
	return -1;
}

void Russion::Test()
{
	char sz[200] ;

	sprintf_s(sz,"point.x=%d,point.y=%d\n LeftAndRight=%d",mLeftTopPoint.x,mLeftTopPoint.y,LeftAndRight());
	
	AfxMessageBox(sz);

}

void Russion::RotateBlock()   //������ת
{
	int i,j;
	int k = 3,l=3;

	ClearBlock(mRolateBlock);
	ClearBlock(mCurrentBlock);
	ClearBlock(mBufferBlock);

	for(i=0;i<=3;i++)   //����ת
	{
		for(j=0;j<=3;j++)
		{
			if(mOldBlock[i][j]==1)
			{
				mRolateBlock[j][3-i] = mOldBlock[i][j];   //temp��ŵ�Ϊ��ת90�ȵ�will
			}
		}
	}

	for(i=0;i<=3;i++)         //�ҵ������Ͻǵķ���������
	{
		for(j=0;j<=3;j++)
		{
			if(mRolateBlock[i][j]==1)
			{
				if(k>=i) k=i;
				if(l>=j) l=j;
			}
		}
	}


	for(i=0;i<=3;i++)   //��ֵbufblock��ɱ任
	{
		for(j=0;j<=3;j++)
		{
			if(mRolateBlock[i][j]==1)
			{
				mBufferBlock[i-k][j-l]=1;
			}
		}
	}

	//���ж��Ƿ�Խ��������Ѵ��ڵķ����ͻ
	for(i=0;i<=3;i++)
	{
		for(j=0;j<=3;j++)
		{

			if (mBufferBlock[i][j] == 1 && game[i + mLeftTopPoint.x][j + mLeftTopPoint.y] == 1)
			{
				return;
			}

			if (mBufferBlock[i][j] == 1 && mLeftTopPoint.y + j > MAX_COL)
			{
				return;
			}

			if (mBufferBlock[i][j] == 1 && mLeftTopPoint.y + j < 1)
			{
				return;
			}

			if (mBufferBlock[i][j] == 1 && mLeftTopPoint.x + i > MAX_ROW)
			{
				return;
			}

		}
	}

	ClearBlock(mOldBlock); //���will

	for (i = 0; i <= 3; i++)   //��ֵwill�����ת
	{
		for (j = 0; j <= 3; j++)
		{
			if (mBufferBlock[i][j] == 1)
			{
				mOldBlock[i][j] = 1;
			}
		}
	}
}

void Russion::RemoveLine()  //����
{
	int i, j, k;
	int sum = 0;

		for(i=0;i<=26;i++)
		{
			for(j=0;j<=18;j++)
			{
				if(game[i][j]==1) 
				{
					sum++;

				}
			}
			if(sum>=19)   //���������������ȥ
				{
				k = i;  //��������
				break;
				}
			else         //�����������������㣬���¼���
				{
				sum=0;
				}
		}

		if(sum>=19)
		{

		for(i=0;i<=18;i++)
		{
			game[k][i]=0;  

		}

		for(i=0;i<=26;i++)
		{
			for(j=0;j<=18;j++)
			{
			game[k][j]=game[k-1][j];    //���е�������
			}
		}

		for(i=26;i>=0;i--)   //����������
		{
			for(j=0;j<=18;j++)
			{
				if(game[i][j]== 1 && game[i-1][j]==0)
				{
					game[i][j]=0;
				}
			}
		}

		Sleep(100);

	}
		return;
}

bool Russion::TheEnd()
{
     int m = 0;  // ��¼�������

	 int i,j;

	for(j=0;j<=26;j++)
	{
		for(i=0;i<=18;i++)
		{
			if(game[i][j]==1)
			{
				m++;
				continue;
	
			}
		}
	}

	if(m>=26) return true;

	return false;
}
