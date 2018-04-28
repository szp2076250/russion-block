
#if !defined(AFX_RUSSION1_H__6CE91669_EBD6_4177_A860_7C1684C3CB86__INCLUDED_)
#define AFX_RUSSION1_H__6CE91669_EBD6_4177_A860_7C1684C3CB86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef int block[4][4];

#define MAX_ROW 26
#define MAX_COL 17

struct Russion  
{
	bool TheEnd();
	void RemoveLine();
	void RotateBlock();
	void Test();
	int BlockHeightLength();
	int BlockWidthLength();

	bool CanNotDown();
	bool LeftAndRight();

	void Change(void);
	void UpdateBackGround(CDC * pDC);  
	void ZeroBackGround();

	bool m_IsCreat;
	void DrawBlock(CDC * pDC);  
	void MoveBlocks(int direct);    
	void ClearBlock(block S);   
	void GetABlock();          
	void Clear(CDC *pDC); 
	void ClearWill(CDC * pDC);
	void ClearBefore(void);

	Russion();
	void IniBlock();				
	void DrawBackground(CDC * pdc);  
	bool mGameStart;				 
	bool mGamePause;                 
	bool mAdvanceVersion;			 
	bool mGameStop;					 
	bool mCanMove;					 
	bool mRotateBlock;				

	block mCurrentBlock;   
	block mOldBlock; 
	block mRolateBlock;				
	block mAfterBlock; 
	block mBufferBlock; 

	int game[100][100];				

	CPoint mLeftTopPoint ;  

	int mRow;  
	int mCol; 

	int iKindOfBlocks; 
	float mSpeed;

	CBitmap mBlockRed;  
	CBitmap mBlockGreen; 
	CBitmap mBlockPing;  
	CBitmap mBlockBlue;  
	CBitmap mBackGround;
	CBitmap mBlockBitmap;         

	virtual ~Russion();

};

#endif // !defined(AFX_RUSSION1_H__6CE91669_EBD6_4177_A860_7C1684C3CB86__INCLUDED_)
