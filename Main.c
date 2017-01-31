#include"Queens.h"

HeadNode *NodeHeadHead, *NodeHeadLast, *NodeHeadCurrent;
clock_t start, end;
int AnswerCount, ri;
int NodeCount;
const double Parameter[5][9] = 
{
	{ 0.000, 0.000, -0.584, -0.001, 0.239, -0.132, 0.303, 0.427, -0.983 },
	{ 0.000, 0.000, 0.000, 0.090, 0.162, 0.071, 0.211, 0.236, -1.924 },
	{ 0.000, 0.000, 0.000, 0.000, 0.229, 0.131, 0.114, 0.126, -0.776 },
	{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.217, 0.238, 0.121, -0.342 },
	{ 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.456, 0.285, -0.195 },
};
const double Limit[5] = { 0.8, 1.8, 0.8, 0.6, 1 };

int main(void)
{
	for (enum Calculation (Approach) = 0; Approach <= 6; Approach++)
	{
		AnswerCount = 0;
		NodeCount = 0;
		start = clock();
		for (ri = 1; ri <= 10000; ri++)
		{
			Init();
			for (int i = 0; i < 8; i++)
			{
				PlaceQueen(i);
				//Print(i + 1);
				//system("pause");
				//system("cls");
				ValueJudgement(Approach, i);
			}
			CleanApp();
		}
		end = clock();
		printf("Way%d:\nTime = %dms\nNodeCount = %d\nAnswerCount = %d\n\n", Approach, end - start, NodeCount, AnswerCount);
	}
	system("pause");
}

void Init()
{
	NodeHeadHead = NodeHeadLast = NodeHeadCurrent = (HeadNode*)malloc(sizeof(HeadNode));
	NodeHeadHead->NodeHead = NodeHeadHead->NodeCurrent = (Node*)malloc(sizeof(Node));

	memset(NodeHeadHead->NodeHead->QueensPosition, 0, 8 * sizeof(int));
	NodeHeadHead->NodeHead->QueensPosition[0] = -1;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			NodeHeadHead->NodeHead->DELTA[i][j] = TRUE;

	NodeHeadHead->NodeHead->AvailablePositionCount = 64;
	NodeHeadHead->NodeHead->Value = 0;

	NodeHeadHead->NodeHead->nextThis = NULL;
	NodeHeadHead->nextHead = NULL;
}

void PlaceQueen(int line)
{
	Node *temp = NodeHeadLast->NodeHead;
	
	CreateNodeHead();

	while (temp != NULL)
	{
		for (int i = 0; i < 8; i++)
		{
			if (temp->DELTA[line][i])
			{
				AddNode(temp, line, i);
				
				if (line == 7 && ri == 1)
					AnswerCount++;
				if (ri == 1)
					NodeCount++;
			}
		}
		temp = temp->nextThis;
	}
	NodeHeadLast = NodeHeadLast->nextHead;
}

void CreateNodeHead()
{
	HeadNode *temp = (HeadNode*)malloc(sizeof(HeadNode));
	NodeHeadCurrent->nextHead = temp;
	NodeHeadCurrent = NodeHeadCurrent->nextHead;
	NodeHeadCurrent->nextHead = NULL;
	NodeHeadCurrent->NodeHead = NodeHeadCurrent->NodeCurrent = NULL;
}

void AddNode(Node *Last, int PositionX, int PositionY)
{
	Node *temp = (Node*)malloc(sizeof(Node));

	temp->AvailablePositionCount = Last->AvailablePositionCount;

	CopyQueensPosition(Last, temp);
	temp->QueensPosition[PositionX] = PositionY;

	CopyDeltaMatrix(Last, temp);
	SetRestrict(temp, PositionX, PositionY);

	CalcValue(temp, PositionX);

	temp->nextThis = NULL;

	if (NodeHeadCurrent->NodeHead == NULL)
		NodeHeadCurrent->NodeHead = NodeHeadCurrent->NodeCurrent = temp;
	else
	{
		NodeHeadCurrent->NodeCurrent->nextThis = temp;
		NodeHeadCurrent->NodeCurrent = temp;
	}
}

void ValueJudgement(enum Calculation Approach, int StepNumber)
{
	switch (Approach)
	{
	case Enumeration: 
		break;
	case MaximLikelihood6:
		if (StepNumber >= 6)
			DeleteBadNode();
		break;
	case MaximLikelihood5:
		if (StepNumber >= 5)
			DeleteBadNode();
		break;
	case MaximLikelihood4:
		if (StepNumber >= 4)
			DeleteBadNode();
		break;
	case MaximLikelihood3:
		if (StepNumber >= 3)
			DeleteBadNode();
		break;
	case MaximLikelihood2:
		if (StepNumber >= 2)
			DeleteBadNode();
		break;
	case Optimized:
		DeleteBadNodeOptimized(StepNumber);
		break;
	default:
		break;
	}
}

void DeleteBadNode()
{
	Node *current = NodeHeadCurrent->NodeHead, *last = NULL;
	int MaxAvailablePosition;

	MaxAvailablePosition = CalcMaxAvailablePosition(NodeHeadCurrent->NodeHead);
	while (current != NULL)
	{
		if (current->AvailablePositionCount < MaxAvailablePosition)
		{
			current = current->nextThis;

			if (last == NULL)
			{
				free(NodeHeadCurrent->NodeHead);
				NodeHeadCurrent->NodeHead = NULL;
				NodeHeadCurrent->NodeHead = current;
			}
			else
			{
				free(last->nextThis);
				last->nextThis = NULL;
				last->nextThis = current;
			}
		}
		else
		{
			last = current;
			current = current->nextThis;
		}
	}
}

void DeleteBadNodeOptimized(int StepNumber)
{
	if (StepNumber >= 1 && StepNumber <= 5)
	{
		Node *current = NodeHeadCurrent->NodeHead, *last = NULL;

		while (current != NULL)
		{
			if (current->Value < Limit[ StepNumber - 1 ])
			{
				current = current->nextThis;

				if (last == NULL)
				{
					free(NodeHeadCurrent->NodeHead);
					NodeHeadCurrent->NodeHead = current;
				}
				else
				{
					free(last->nextThis);
					last->nextThis = current;
				}
			}
			else
			{
				last = current;
				current = current->nextThis;
			}
		}
	}
}