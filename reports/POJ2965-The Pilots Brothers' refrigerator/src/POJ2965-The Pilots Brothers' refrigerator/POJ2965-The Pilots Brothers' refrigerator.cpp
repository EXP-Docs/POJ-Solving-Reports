/*
	Author:     Exp
	Date:       2017-12-04
	Code:       POJ 2965
	Problem:    The Pilots Brothers' refrigerator
	URL:        http://poj.org/problem?id=2965
*/

/*
	���������
	  ��һ���䣬����4x4��16�����أ�"-"״̬��ʾopen��"+"״̬��close���� 
	  ���ı�һ������״̬ʱ���ÿ��������С��е�ȫ������״̬Ҳ��ͬʱ�ı䡣 

	  ����һ������״̬���ʴӸ�״̬��ʼ��ʹ�����п��ش򿪣�ȫ"-"����
	  ������Ҫ�������ٲ������Ѳ������̴�ӡ��������ӡ���������ص��������꣬�����1��ʼ��


	����˼·��
	  ����� POJ 1753 �Ľ���˼·��һģһ���ģ�ֻ�Ǵ��ڼ�������㣬ʹ�ý��⼼����΢�����һ��.
	  û�� POJ 1753 ��ͬѧ��ȥ�������⣬������ٻ�ͷ������.

	  ������͵�����󲿷ֶ���ֱ���������Լ� POJ 1753 �Ĵ��룬
	  �����ϸ�Ľ���˼·�Ͳ��ٸ����ˣ�����˼·���� ���ö������״̬��Ȼ����������״̬���
	  
	  
	  ����ֻ�г�����Ĳ��죬�Լ���Բ���Ĵ����ַ�����������Ⲣ���POJ 1753��ǰ�����ٿ�����

		�� ����״ֻ̬��ȫ0һ�֣������п��ش򿪣��� ��POJ-1753��ȫ0��ȫ1����.
		   ��˱���ֻ��Ҫö�ٴ�ȫ0״̬��������״̬�Ĺ��̣����迼��ȫ1

		�� ��ת����Ӱ�����ȫ��+ȫ�й�7�����أ���POJ-1753���������ӱ�Ӱ��

		�� �� POJ-1753 һ�������ֻ�ܲ��ظ��ز���16�Σ���ͬ������2^16=65536��״̬��
		   �����ڷ�ת�������ص�Ӱ�췶Χ�ı��ˣ���65536�ֲ��ظ�״̬���ǲ��ظ���
		   ��֤���ԣ���BFS��ӡ����״̬�õ�ӡ֤��

		�� ����Ҫ�������ת���صĹ��̣�����Ŀ��עΪSpecial Judge���༴һ���⣩

		   ������Ϊ����ͬ�������ɸ����أ�����˳�򲻻�Ӱ�����յ����״̬, 
		   ��˷�ת�����ǹ̶��ģ���ת˳�������ӡ��������һ����Ĵ���
		   �������ڲ������ظ�״̬����ת�����ǹ̶��ģ�

		   �ڱ���ͬ���ο� POJ-1753 ��״̬ѹ����ʽ����ʹ�� unsigned int �洢����״̬��
		   ��16λΪ�����룬��16λΪ״̬�룬��ô���в������Ŀ��ض����ԴӸ�16λ��ȡ��
		   ����ͨ�������ڲ������еĶ�����λ�ã����Է���ӳ�䵽4x4������������꣨�г�4����ģ4��
*/

#include <iostream>
using namespace std;


// �޷�������(32λ)�����ڼ�¼���ؾ�����룬��ҪΪ�˱���int32�ĸ���Ӱ��  
// ��ʼ���ؾ���״̬Ϊȫ0��ȫ"-"����open��  
// ��16λΪ���ؾ������λ���������Ŀ���λ�ñ��Ϊ1  
// ��16λΪ���ؾ���״̬λ, ��¼��ǰ���ؾ���״̬��"+"����Ϊ1:close��"-"����Ϊ0:open��  
typedef unsigned int _UINT;


const static int MAX_STEP = 16;			// �ɷ�ת���ؾ���������
const static int MAX_STATUS = 65536;	// ��״̬�� = 2^16


// ���ؾ���״̬���룺����תλ��i�Ŀ���ʱ,STATUS_MASKS[i]Ϊ������Ӱ�������λ�� 
// λ��i����4x4���ؾ����ڣ������ҡ����ϵ��°�0-15���α���  
const static int STATUS_MASKS[16] = {
	0x0000111F, 0x0000222F, 0x0000444F, 0x0000888F,
	0x000011F1, 0x000022F2, 0x000044F4, 0x000088F8,
	0x00001F11, 0x00002F22, 0x00004F44, 0x00008F88,
	0x0000F111, 0x0000F222, 0x0000F444, 0x0000F888
};


/**
 * 4x4�Ŀ��ؾ������
 */
class SwitchGroup {
	public:
		SwitchGroup();
		~SwitchGroup();
		void print(int status);		// ��ӡ��ȫ0��open����ָ��״̬����С���������Լ���������
		
	private:
		void bfsAllStatus(void);				// ��¼���ظ��ط���1-16���ɵõ������п��ؾ���״̬
		_UINT filp(_UINT _switch, int bitPos);	// �������ؾ�����ĳ��ָ��λλ�õĿ���
		
		int toStatus(_UINT _switch);		// �ӿ��ؾ��������ȡ״̬��Ϣ
		int getMaxBitPos(_UINT _switch);	// �ӿ��ؾ��������ȡ������Ϣ������������ת��ŵ�λ��
		int getFilpCount(_UINT _switch);	// �ӿ��ؾ��������ȡ������Ϣ����ȡ��ȫ0״̬��ʼ�����������صĴ���

	private:
		_UINT* switchs;		// ��¼��ȫ0(open)��ʼ����ÿ��״̬�Ŀ��ؾ������
};


int main(void) {
	// һ�μ�������п��ؾ���״̬���
	SwitchGroup* switchGroup = new SwitchGroup();

	// �������뿪�ؾ���״̬ ���
	int switchStatus = 0;
	int byteCnt = 0;
	char byteBuff[5] = { '\0' };
	while(cin >> byteBuff && ++byteCnt) {
		int offset = 4 * (byteCnt - 1);
		for(int i = 0; i < 4; i++) {
			if(byteBuff[i] == '+') {	// -���Ϊ0, +���Ϊ1
				switchStatus |= (0x00000001 << (i + offset));
			}
		}

		// ÿ����4���ֽ����һ��
		if(byteCnt >= 4) {
			switchGroup->print(switchStatus);
			
			byteCnt = 0;
			switchStatus = 0;
		}
	}
	delete switchGroup;
	return 0;
}


/**
 * ���캯��
 */
SwitchGroup::SwitchGroup() {
	this->switchs = new _UINT[MAX_STATUS];
	memset(switchs, -1, sizeof(_UINT) * MAX_STATUS);

	bfsAllStatus();
}


/**
 * ��������
 */
SwitchGroup::~SwitchGroup() {
	delete[] switchs;
	switchs = NULL;
}


/**
 * ��ʼ�����ظ��ط���1-16���ɵõ������п��ؾ���״̬
 *
 *   ������������״̬�����ظ���״̬���ﵽ65536����
 *   ���POJ1753��״̬��Ҫ��öֻࣨ��4096����
 *   ����POJ1753���Զ���Ч״̬��֦����������������״̬����Ч�����޷�������֦
 *   ����������£���������POJ1753����ʹ��STL��set����ά��BFS���У�
 *   �������Ϊset��ά�����۹���TLE
 *
 *   ��˱��⻹����Ϊ�����BFS���з�����������״̬
 *   ���������ǿ��Ը��ݿ���״̬�ԳƷֲ������Լ�֦�ģ�������һ������������һ�����㣬���������ԣ�
 */
void SwitchGroup::bfsAllStatus(void) {
	const int ALL_OPEN = 0;
	_UINT bfsQueue[MAX_STATUS];		// ��ʼ״̬�����ؾ���ȫopen
	int head = 0, tail = 0;
	bfsQueue[tail++] = ALL_OPEN;

	while(head < tail) {
		_UINT lastSwitch = bfsQueue[head++];
		int status = toStatus(lastSwitch);	// ���θ�16λ����λ���õ���16λ���������ؾ���״̬
		switchs[status] = lastSwitch;		// ���濪�ؾ���״̬��Ӧ�Ŀ��ؾ������

		// ��֦1�������Ǵӵ�λ��ſ�ʼ��ת�ģ�Ϊ�˲��ظ���ת���أ�����һ���ؾ���״̬�����λ��ſ�ʼ���� 
		for(int pos = getMaxBitPos(lastSwitch) + 1; pos < MAX_STEP; pos++) {
			_UINT nextSwitch = filp(lastSwitch, pos);	// ��ת���صõ���һ�����ؾ������
			bfsQueue[tail++] = nextSwitch;
		}
	}
}


/**
 * ��ת���ؾ�����ĳ��ָ��λλ�õĿ���,
 *  �˲�����ͬʱ�ı俪�ؾ������Ĳ���λ����16λ����״̬λ����16λ��
 * @param _switch ��תǰ�Ŀ��ؾ������
 * @param bitPos Ҫ��ת�Ŀ���λ��, ȡֵ��ΧΪ[0, 15]��
 *				���ζ�Ӧ4x4�����ϴ����ҡ����϶��µı�ţ�Ҳ��Ӧ���������ӵ͵��ߵĽ���λ
 * return ��ת��Ŀ��ؾ������
 */
_UINT SwitchGroup::filp(_UINT _switch, int bitPos) {
	_UINT OP_MASK = 0x00010000 << bitPos;		// ��16λ:��ǰ����λ
	_UINT STATUS_MASK = STATUS_MASKS[bitPos];	// ��16λ:���״̬λ
	return (_switch ^ (OP_MASK | STATUS_MASK));	// �������̱���
}


/**
 * �ӿ��ؾ��������ȡ���ؾ���״̬��Ϣ����16λ��
 * return ���ؾ���״̬��Ϣ
 */
int SwitchGroup::toStatus(_UINT _switch) {
	const _UINT MASK = 0x0000FFFF;
	return (int) (_switch & MASK);
}


/**
 * �ӿ��ؾ��������ȡ������Ϣ����16λ��������������ת��ŵ�λ��
 * @param _switch ���ؾ������
 * return û�в������򷵻�-1�����򷵻�0-15
 */
int SwitchGroup::getMaxBitPos(_UINT _switch) {
	_UINT MASK = 0x80000000;
	int bitPos = -1;
	for(int i = MAX_STEP - 1; i >= 0; i--) {
		if((_switch & MASK) == MASK) {	// ע�������, ==���ȼ���&Ҫ��
			bitPos = i;
			break;
		}
		MASK >>= 1;
	}
	return bitPos;
}


/**
 * �ӿ��ؾ��������ȡ������Ϣ����16λ������ȡ��ȫ0״̬��ʼ�����������صĴ���
 * @param _switch ���ؾ������
 * return ����ת����
 */
int SwitchGroup::getFilpCount(_UINT _switch) {
	const _UINT MASK = 0xFFFF0000;
	_switch &= MASK;	// ���ε�16λ��״̬λ

	// �жϸ�16λ����λ�ж��ٸ�1, ��Ϊ��ת����
	int cnt = 0;
	while(_switch > 0) {
		_switch = (_switch & (_switch - 1));
		cnt++;
	}
	return cnt;
}


/**
 * ��ӡ��ȫ0��open����ָ�����ؾ���״̬����С���������Լ���������
 * @param status ���ؾ���״̬
 * return ��С�����������ɴ��򷵻�-1��
 */
void SwitchGroup::print(int status) {
	if(status >= 0 && status < MAX_STATUS) {
		_UINT _switch = switchs[status];

		// ��ӡ����
		int step = getFilpCount(_switch);
		cout << step << endl;

		// ��ӡ��ת���ع���
		for(int mask = 0x00010000, bit = 0; bit < MAX_STEP; bit++, mask <<= 1) {
			if((_switch & mask) > 0) {
				cout << (bit / 4) + 1 << " " << (bit % 4) + 1 << endl;
			}
		}
	}
}
