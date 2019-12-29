/*
	Author:     Exp
	Date:       2017-11-30
	Code:       POJ 1083
	Problem:    Moving Tables
	URL:		http://poj.org/problem?id=1083
*/

/*
	���������
	 �Ƶ���400�����䣬���±�ŶԳƷֲ���һ����������
	 1 3 5 ... 397 399
	    ����������
	 2 4 6 ... 398 400

	 ����Ҫ�ӷ���s->t�����ӣ���N�鷿����Ҫ�����ӣ�ÿ��һ��10����(�����������������Զ).
	 ����ĳ�鷿�䣬�������ڼ� s->t ֮������Ȼᱻռ�ã�
	 �������鷿����û��ʹ�õ�ռ�õ����ȣ����ͬʱ�ᣬ����Ҫ�ȴ�.
	 �ر�أ���Ե����䷿������һ������, ��������3�����ȱ�ռ���ˣ���ͬ�ڷ���4�����ȱ�ռ����.

	 ����N����Ҫ������ӣ�����С���԰����ʱ��.


	����˼·:
	 �о������е������ڶ��̵߳�ͬ�����ⳡ������.

	 �� ������Ե����䷿����ͬһ�����ȣ�Ϊ�˷��㴦�����⣬���԰�������������ת����ż�����䣬��֮���.
	    �� 1->6 �ɵȼ�ת���� 2->6�� ����ֻ��Ҫ��עһ��ķ��伴�ɣ���200�䣩
	 �� ���ݷ���Ŷ����Ƚ��зָ�ɷָ��200������. �ڴӷ���s->t�������ڼ䣬����ʹ�õ���ÿ�����ȼ���+1
	 �� �������Ӱ����ͳ��ÿ�����ȵļ���ֵ������ֵ������������ܹ���Ҫ��ռ�õĴ�����,
	    ������Ŀ�������ǰᶯ�ڼ���ƶ���������(��ȶ��̵߳�������)��
		�������һ������ֵ*10���� �����������С����ʱ�䣨��ΪֻҪ���ȱ�ռ�ţ���ֻ������һ���ٰᣬ����ͬʱ�ᣩ

*/

#include <iostream>
using namespace std;

const static int ROOM_NUM = 400;	// ��󷿺�
const static int TIME_UNIT = 10;	// ʱ�䵥λ

/* 
 * ��ż������ת������������
 * @param even ż������
 * return ��������
 */
int toOdd(int even);

/* 
 * �������
 */
void solve(void);


int main(void) {
	int testCase = 0;
	cin >> testCase;
	for(int t = 0; t < testCase; t++) {
		solve();
	}

	//system("pause");
	return 0;
}


int toOdd(int even) {
	return (even % 2 == 0 ? even - 1 : even);
}


void solve(void) {
	int useCnt[ROOM_NUM] = { 0 };		// ÿ������ǰ�����ȱ�ʹ�õĴ���
	int maxUseCnt = 0;					// ��ʹ�����Ĵ���

	int moveCnt = 0;					// ��Ҫ�ᶯ����������
	cin >> moveCnt;
	int* fromRooms = new int[moveCnt];	// ��㷿�伯
	int* toRooms = new int[moveCnt];	// �յ㷿�伯
	for(int i = 0; i < moveCnt; i++) {
		int from, to;
		cin >> from >> to;

		// ʹ����С����ǰ��
		fromRooms[i] = (from <= to ? from : to);
		toRooms[i] = (from > to ? from : to);

		// �ѷ���ȫ��ת��������
		fromRooms[i] = toOdd(fromRooms[i]);	
		toRooms[i] = toOdd(toRooms[i]);

		// ��ط���ǰռ�õ����ȱ�ʹ�ô���+1
		for(int roomId = fromRooms[i]; roomId <= toRooms[i]; roomId += 2) {
			useCnt[roomId]++;
			if(maxUseCnt < useCnt[roomId]) {
				maxUseCnt = useCnt[roomId];	// �Ǽ�����ʹ�ô���
			}
		}
	}
	delete[] fromRooms;
	delete[] toRooms;

	// ������С��ʹ��ʱ��
	maxUseCnt = (maxUseCnt <= 0 || maxUseCnt > moveCnt ? moveCnt : maxUseCnt);
	int minUsedTime = maxUseCnt * TIME_UNIT;
	cout << minUsedTime << endl;
}
