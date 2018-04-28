
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
	
	mCanMove = false; //能移动
	mGameStart = false;
	mGamePause = false;
	mAdvanceVersion = false;
	m_IsCreat = false;
	mGameStop = false;
	mRotateBlock = false;   
	mSpeed = 4;  

	mRow = 20;   //20列26行
	mCol = 26;

	mLeftTopPoint.x = 0;     //方块开始下落的行数
	mLeftTopPoint.y = 19/2;    //方块开始下落的列数

	ZeroBackGround();   //将界面数组清空
	GetABlock();
}

//重置随机数种子
//判断是否是高级版 高级版本随机(1-9) 低版本随机(1-6)
//清空方块数组。指定相应的方块数组哪个位置需要绘制 就设为1
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
	case 7:              //扩展
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

//根据方向direct 移动方块
//1代表上 2代表下 3代表左 default代表右 
//按了上的话调用 RotateBlock 旋转方块 
//按了左和右：
//          如果在可以移动(不会超过方块的边界并且和别的方块没有碰撞)的情况下，就移动
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
	CDC dcm;   //记忆DC
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
			game[i][j] = 0 ; //全部为空
}

//绘制整个背景数组 如果背景数组的值为0 就是白色的
// 如果背景数组的值为1 就绘制方块。
// 然后把之前绘制的擦除。准备下次绘制
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

//将背景数组相应的位置填1  
//之后绘制所有值为1的元素。
void Russion::Change()
{
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			if(mOldBlock[i][j]==1)
				game[i+mLeftTopPoint.x][j+mLeftTopPoint.y]=1;
}

//将背景数组值的之前绘制的位置清除
void Russion::ClearBefore()
{
	for(int i=0;i<=3;i++)
		for(int j=0;j<=3;j++)
			if(mAfterBlock[i][j]==1)
				game[i+mLeftTopPoint.x][j+mLeftTopPoint.y]=0;

}

//在左右有方块的时候不能移动
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

//判断是否已经和最下面的方块碰撞或者和边界碰撞了
//首先判断了是否超出边界
//然后不能超过已经存在的下面方块
//检查最下面一行是否和背景数组冲突
bool Russion::CanNotDown()
{	

	//不能超过最下列
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


	//不能超过最下面已经存在的方块
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

//从下向上
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

void Russion::RotateBlock()   //矩阵旋转
{
	int i,j;
	int k = 3,l=3;

	ClearBlock(mRolateBlock);
	ClearBlock(mCurrentBlock);
	ClearBlock(mBufferBlock);

	for(i=0;i<=3;i++)   //先旋转
	{
		for(j=0;j<=3;j++)
		{
			if(mOldBlock[i][j]==1)
			{
				mRolateBlock[j][3-i] = mOldBlock[i][j];   //temp存放的为旋转90度的will
			}
		}
	}

	for(i=0;i<=3;i++)         //找到最左上角的方块行列数
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


	for(i=0;i<=3;i++)   //赋值bufblock完成变换
	{
		for(j=0;j<=3;j++)
		{
			if(mRolateBlock[i][j]==1)
			{
				mBufferBlock[i-k][j-l]=1;
			}
		}
	}

	//先判断是否越界或者与已存在的方块冲突
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

	ClearBlock(mOldBlock); //清空will

	for (i = 0; i <= 3; i++)   //赋值will完成旋转
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

void Russion::RemoveLine()  //消行
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
			if(sum>=19)   //如果等于列数则消去
				{
				k = i;  //保存行数
				break;
				}
			else         //如果不等于列数则归零，重新计数
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
			game[k][j]=game[k-1][j];    //本行等于上行
			}
		}

		for(i=26;i>=0;i--)   //最上行消零
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
     int m = 0;  // 记录最大行数

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
