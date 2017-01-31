#include"Queens.h"

extern HeadNode *NodeHeadHead, *NodeHeadLast, *NodeHeadCurrent;
extern const double Parameter[5][9];

void SetRestrict(Node *pNode, int PositionX, int PositionY)
{	
	for (int i = 0; i < 8; i++)
	{
		if (pNode->DELTA[PositionX][i] == TRUE)
		{
			pNode->DELTA[PositionX][i] = FALSE;
			pNode->AvailablePositionCount--;
		}
		if (pNode->DELTA[i][PositionY] == TRUE)
		{
			pNode->DELTA[i][PositionY] = FALSE;
			pNode->AvailablePositionCount--;
		}
	}

	int x = PositionX, y = PositionY;
	while (x >= 0 && y >= 0)
	{
		if (pNode->DELTA[x][y] == TRUE)
		{
			pNode->DELTA[x][y] = FALSE;
			pNode->AvailablePositionCount--;
		}
		x--; y--;
	}	

	x = PositionX; y = PositionY;
	while (x < 8 && y < 8)
	{
		if (pNode->DELTA[x][y] == TRUE)
		{
			pNode->DELTA[x][y] = FALSE;
			pNode->AvailablePositionCount--;
		}
		x++; y++;
	}

	x = PositionX; y = PositionY;
	while (x >= 0 && y < 8)
	{
		if (pNode->DELTA[x][y] == TRUE)
		{
			pNode->DELTA[x][y] = FALSE;
			pNode->AvailablePositionCount--;
		}
		x--; y++;
	}

	x = PositionX; y = PositionY;
	while (x < 8 && y >= 0)
	{
		if (pNode->DELTA[x][y] == TRUE)
		{
			pNode->DELTA[x][y] = FALSE;
			pNode->AvailablePositionCount--;
		}
		x++; y--;
	}
}

void CopyQueensPosition(Node *ReadNode, Node *WrightNode)
{
	for (int i = 0; i < 8; i++)
		WrightNode->QueensPosition[i] = ReadNode->QueensPosition[i];
}

void CopyDeltaMatrix(Node *ReadNode, Node *WrightNode)
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			WrightNode->DELTA[i][j] = ReadNode->DELTA[i][j];
}

int CalcMaxAvailablePosition(Node *NodeHead)
{
	int max = 0;
	Node *temp = NodeHead;

	while (temp != NULL)
	{
		if (temp->AvailablePositionCount > max)
			max = temp->AvailablePositionCount;
		temp = temp->nextThis;
	}

	return max;
}

void CalcValue(Node *pNode, int StepNumber)
{
	pNode->Value = 0.0;

	if (StepNumber >= 1)
	{
		for (int x = 2; x < 8; x++)
		{
			for (int y = 0; y < 8; y++)
			{
				if (pNode->DELTA[x][y] == TRUE)
					pNode->Value += Parameter[StepNumber - 1][x];
			}
		}
		pNode->Value += Parameter[StepNumber][8];
	}
}

int CalcMaxValue(Node *NodeHead)
{
	int max = 0;
	Node *temp = NodeHead;

	while (temp != NULL)
	{
		if (temp->Value > max)
			max = temp->Value;
		temp = temp->nextThis;
	}

	return max;
}

void Print(int StepNumber)
{
	Node *temp = NodeHeadCurrent->NodeHead;
	
	if (temp == NULL)
	{
		printf("Searching failed in step %d !\n", StepNumber);
		system("pause");
		exit(0);
	}

	if (StepNumber < 8)
		printf("When %d Queens Placed:\n\n", StepNumber);	
	else if (StepNumber == 8)
		printf("Answer:\n\n");

		while (temp != NULL)
		{
			PrintChessBoard(temp, StepNumber);
			printf("          Remaining available position: %d\n\n", temp->AvailablePositionCount);
			temp = temp->nextThis;
		}
}

void PrintChessBoard(Node *pNode, int StepNumber)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			if (pNode->QueensPosition[x] == y && x < StepNumber)
				printf("O");
			else if (pNode->DELTA[x][y] == FALSE)
				printf("x");
			else
				printf(".");
		}
		if (x < 7)
		printf("\n");
	}
}

void CleanApp()
{
	HeadNode *Headcurrent = NodeHeadHead, *Headlast = NULL;
	Node *current = NULL, *last = NULL;

	while (Headcurrent != NULL)
	{
		current = Headcurrent->NodeHead;
		while (current != NULL)
		{
			last = current;
			current = current->nextThis;
			free(last);
		}

		Headlast = Headcurrent;
		Headcurrent = Headcurrent->nextHead;
		free(Headlast);
	}
}