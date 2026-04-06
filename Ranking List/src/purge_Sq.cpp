#include "purge_Sq.h"
#include <string>

void purge_Sq(LeaderBoard* LB) {
	//为空指针或者元素个数小于等于1时无需去重
	if (LB == nullptr || LB->size <= 1)
		return;
	//定义有效边界k,k为下一个元素要插入的位置
	int k = 0;
	for (int i = 0; i < LB->size; i++) {
		bool duplicate = false;
		//在已保留的数据中查询
		for (int j = 0; j < k; j++) {
			if (LB->elements[i].name == LB->elements[j].name) {
				duplicate = true;
				break;
			}
		}
		//如果与之前的数据未重复则保留，有效边界后移
		if (!duplicate) {
			LB->elements[k] = LB->elements[i];
			k++;
		}
	}
	LB->size = k;
}
