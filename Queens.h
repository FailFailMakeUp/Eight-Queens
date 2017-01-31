#pragma warning(disable:4996)
#ifndef _QUEENS_H_
#define _QUEENS_H_

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

typedef int BOOL;
#define TRUE  1
#define FALSE 0

enum Calculation
{
	Enumeration = 0,
	MaximLikelihood6 = 1,
	MaximLikelihood5 = 2,
	MaximLikelihood4 = 3,
	MaximLikelihood3 = 4,
	MaximLikelihood2 = 5,
	Optimized = 6
};

typedef struct MyNode
{
	int QueensPosition[8];
	BOOL DELTA[8][8];
	int AvailablePositionCount;
	double Value;
	struct MyNode *nextThis;
} Node;

typedef struct MyHeadNode
{
	Node *NodeHead;
	Node *NodeCurrent;
	struct MyHeadNode *nextHead;
} HeadNode;


//Main.c
void Init();
void PlaceQueen(int line);
void CreateNodeHead();
void AddNode(Node *Last, int PositionX, int PositionY);
void ValueJudgement(enum Calculation Approach, int StepNumber);
void DeleteBadNode();
void DeleteBadNodeOptimized(int StepNumber);

//Util.c
void SetRestrict(Node *pNode, int PositionX, int PositionY);
void CopyQueensPosition(Node *ReadNode, Node *WrightNode);
void CopyDeltaMatrix(Node *ReadNode, Node *WrightNode);
int CalcMaxAvailablePosition(Node *NodeHead);
void CalcValue(Node *pNode, int StepNumber);
void Print(int StepNumber);
void PrintChessBoard(Node *pNode, int StepNumber);
void CleanApp();

#endif