//
// Created by father on 2024/4/9.
//

#ifndef UNTITLED1_ARRAY_H
#define UNTITLED1_ARRAY_H
typedef int element_type ;// 数组元素类型
typedef short int status; //
#define  true 1
#define false 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//  数组定长
const int size = 16;
#ifndef KKK  // 是否是可变数组
typedef struct {// 可变长
    element_type * data_list; // 有序表数组
    int length;// 有序表长度
    int size;// 有序表最大大小
} array ;
#else
typedef struct {// 不可变长
    element_type data_list[size]; // 有序表数组
    int length;// 有序表长度
    int size;// 有序表最大大小
} array ;
#endif
// 创建数组 定长
void init_array(array * a){
#ifndef KKK
    a->data_list = malloc(sizeof(element_type) * size); // 申请空间
    if (a->data_list == 0){
        fprintf(stderr,"分配失败");
        exit(-1);
    }
#endif
    a->size = size;
    a->length = 0;
}
#ifndef KKK
// 创建数组，指定长度
void init_array_size(array * a,int size_){
    a->data_list = malloc(sizeof(element_type) * size_);
    if (a->data_list == 0){
        fprintf(stderr,"分配失败");
        exit(-1);
    }
    a->length = 0;
    a->size = size_;
}
// 创建数组，指定长度，全换成0
void init_array_size_0(array * a,int size_){
    a->data_list = malloc(sizeof(element_type) * size_);
    if (a->data_list == 0){
        fprintf(stderr,"分配失败");
        exit(-1);
    }
    a->length = size_;
    a->size = size_;
    for (int i = 0; i < size_; ++i) {
        a->data_list[i] = 0;
    }
}
// 创建数组，指定长度，全换成e
void init_array_size_(array * a,int size_,element_type e){
    a->data_list = malloc(sizeof(element_type) * size_);
    if (a->data_list == 0){
        fprintf(stderr,"分配失败");
        exit(-1);
    }
    a->length = size_;
    a->size = size_;
    for (int i = 0; i < size_; ++i) {
        memcpy(&a->data_list[i],&e,sizeof(element_type));
    }
}
// 赋值数组
void init_array_(array * a,const element_type * begin,const element_type * end){
    int length = end - begin + 1; // 两个指针之间的减法  int一次减4个字节 +1 是数组的长度
    a->data_list = malloc(sizeof(element_type) * length);
    if (a->data_list == 0){
        fprintf(stderr,"分配失败");
        exit(-1);
    }
    memcpy(a->data_list,begin,length * sizeof(element_type));
    a->length = length;
    a->size = length;
}
// 拷贝赋值
void init_array_copy(array * a,const array * b){
    a->data_list = malloc(sizeof(element_type) * b->size);
    if (a->data_list == 0){
        fprintf(stderr,"分配失败");
        exit(-1);
    }
    memcpy(a->data_list,b->data_list,sizeof(element_type) * b->size); // 开辟和b相同的空间
    a->size = b->size;
    a->length = b->length;
}
#endif
// 销毁函数
void destroy_array(array * a){
#ifndef KKK
    free(a->data_list); // 释放申请的空间
#endif
    a->length = a->size = 0; // 防止复用
}
// 判断数组是否为空
status empty_array(array a){
    if (a.data_list == 0 || a.size == 0){ // 数组可能不存在
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    if (a.length == 0)
        return true;
    return false;
}
// 判断数组是否满了
status fall_array(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    if (a.length == a.size)
        return true;
    return false;
}
// 数组大小
size_t size_array(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    return a.size;
}
// 返回数组剩余空间
size_t capacity(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    return a.size - a.length;
}
//  交换两个块 深拷贝
void swap_array(array * a,int i,int j){
    element_type temp;
    memcpy(&temp,&a->data_list[i],sizeof(element_type));
    memcpy(&a->data_list[i],&a->data_list[j],sizeof(element_type));
    memcpy(&a->data_list[j],&temp,sizeof(element_type));
}
// 重新分配空间
status reserve(array * a,int size_){
    if (size_ > a->size){
        element_type * new = realloc(a->data_list,size_ * sizeof(element_type));
        if (new == 0){
            fprintf(stderr,"分配失败");
            exit(-1);
        }
        a->data_list = new;
        a->size = size_;
        return true;
    }
    return false;
}
// 缩小空间
status reserve_(array * a){
    if (a->length < a->size / 4){
        element_type * new = realloc(a->data_list,a->size / 4);
        if (new == 0){
            fprintf(stderr,"分配失败");
            exit(-1);
        }
        a->data_list = new;
        a->size /= 2;
        return true;
    }
    return false;
}
// 新增
status insert_array(array * a,element_type e,int i){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    if (a->length + 1 > a->size){
#ifndef KKK
        reserve(a,a->size*2);
#else
        fprintf(stderr,"该数组无法扩容"); // 定长数组无法扩容
        return false;
#endif
    }
    if (i > a->length){
        fprintf(stderr,"该数组越界");
        return false;
    }
    for (int j = a->length; j > i; --j) {
        memcpy(&a->data_list[j + 1],&a->data_list[j],sizeof(element_type));
    }
    memcpy(&a->data_list[i],&e,sizeof(element_type));
    a->length++;
    return true;
}
// 将一个数组从begin到end拷贝近来
status insert_array_itc(array * a,const element_type * begin,const element_type * end){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    int length = end - begin + 1;
    if (a->length + length > a->size){
#ifndef KKK
        reserve(a,a->size*2);
#else
        fprintf(stderr,"该数组无法扩容");
        return false;
#endif
    }
    for (int i = 0; i < length; ++i) {
        memcpy(&a->data_list[a->length++],begin++,sizeof(element_type));
    }
    a->length+= length;
    return true;
}
// 将一个数组从下标begin到end拷贝近来
status insert_array_at(array * a,element_type e,int begin,int end){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    if (begin >= end){
        fprintf(stderr,"输入无效");
        exit(-1);
    }
    if (a->length + end - begin > a->size){
#ifndef KKK
        reserve(a,a->size*2);
#else
        fprintf(stderr,"该数组无法扩容");
        return false;
#endif
    }
    if (begin > a->length || end > a->size){
        fprintf(stderr,"该数组越界");
        return false;
    }
    for (int j = a->length; j > end; --j) {// 分出部分空间
        memcpy(&a->data_list[j + 1],&a->data_list[j],sizeof(element_type));
    }
    for (int i = begin; i < end; ++i) { //整体赋值
        memcpy(&a->data_list[i],&e,sizeof(element_type));
    }
    a->length += (end - begin);
    return true;
}
// 尾插
status insert_array_end(array * a,element_type e){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    if (a->length + 1 >= a->size){
#ifndef KKK
        reserve(a,a->size * 2);
#else
        fprintf(stderr,"该数组无法扩容");
        return false;
#endif
    }
    memcpy(&a->data_list[a->length],&e,sizeof(element_type));
    a->length++;
    return true;
}
// 删除
status delete_array(array * a,element_type * e,int i) {
    if (a->data_list == 0 || a->size == 0) {
        fprintf(stderr, "该数组不存在");
        exit(-1);
    }
    if (empty_array(*a)) {
        fprintf(stderr, "该数组为空");
        return false;
    }
    if (i >= a->length) {
        fprintf(stderr, "该数组越界");
        return false;
    }
    memcpy(&e, &a->data_list[i], sizeof(element_type));
    for (int j = i; j < a->length; ++j) {
        memcpy(&a->data_list[j], &a->data_list[j + 1], sizeof(element_type));
    }
    a->length--;
    return true;
}
// 尾删
status delete_array_end(array * a,element_type * e){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    if (empty_array(*a)){
        fprintf(stderr,"该数组为空");
        return false;
    }
    memcpy(&e,&a->data_list[a->length - 1],sizeof(element_type));
    a->length--;
    return true;
}
// 删除部分
status delete_array_all(array * a,int start,int end){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    if (empty_array(*a)){
        fprintf(stderr,"该数组为空");
        return false;
    }
    if (start >= a->length || end >= a->length){
        fprintf(stderr,"该数组越界");
        return false;
    }
    for (int i = start,j = end; i != end; ++i,++j) {
        memcpy(&a->data_list[i],&a->data_list[j],sizeof(element_type));
    }
    a->length -= (end - start);
    reserve_(a);
    return true;
}
//清空
void clean_array(array * a){
    a->length = 0;
    reserve_(a);
}
// 返回数组长度
size_t array_length(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"该数组不存在");
        exit(-1);
    }
    return a.length;
}
// 重新分配空间
void resize_array(array * a,int size_){
    if (size_ > a->size){
        reserve(a,size_);
    } else {
        reserve_(a);
    }
}
// 返回首部
element_type * fount(array * a){
    return &a->data_list[0];
}
// 返回尾部
element_type * back(array * a){
    return &a->data_list[a->length - 1];
}
// 伪下标操作
element_type at_array(array * a,int i){
    if (i > a->length){
        fprintf(stderr,"越界");
        return false;
    }
    return a->data_list[i];
}
// 寻找元素 如果找到返回下标
int find_by_array(array * a, element_type e,int (*compare)(const element_type *,const element_type *)){
    for (int i = 0; i < a->length; ++i) {
        if (compare(&a->data_list[i],&e)){
            return i;
        }
    }
    return -1;
}
// 数组比较
status compare(const array * a1,const array * a2){
    if (a1->size != a2->size || a1->length != a2->length) return false;
    for (int i = 0; i < a1->length; ++i) {
        if (a1->data_list[i] != a2->data_list[i]) return false;
    }
    return true;
}
// 数组不相等
status not_compare(const array * a1,const array * a2){
    if (a1->size != a2->size || a1->length != a2->length) return true;
    for (int i = 0; i < a1->length; ++i) {
        if (a1->data_list[i] != a2->data_list[i]) return true;
    }
    return false;
}
// 数组排序
void sort_array(array * a,int (*cmp)(const element_type *,const element_type *)){
    qsort(a->data_list, a->length, sizeof(element_type), (int (*)(const void *, const void *)) cmp);
}
// 数组部分排序
void sort_array_begin_and_end(array * a,int begin,int end,int (*cmp)(const element_type *,const element_type *)){
    qsort(&a->data_list[begin], end - begin, sizeof(element_type), (int (*)(const void *, const void *)) cmp);
}
// 冒泡排序
void bullet_sort(array * a){
    for (int i = 0; i < a->length - 1; ++i) {
        for (int j = 0; j < a->length - 1 - i; ++j) {
            if (a->data_list[j] > a->data_list[j + 1]){
                swap_array(a,j,j+1);
            }
        }
    }
}
// 选择排序
void select_sort(array * a){
    for (int i = 0; i < a->length; ++i) {
        int m = i;
        for (int j = i + 1; j < a->length; ++j) {
            if (a->data_list[m] > a->data_list[j]){
                m = j;
            }
        }
        if (i != m){
            swap_array(a,i,m);
        }
    }
}
// 插入排序
void insert_sort(array * a){
    for (int i = 1; i < a->length; ++i) {
        int key = a->data_list[i];
        int j = 0;
        for (j = i - 1; j >= 0 && a->data_list[j] > key ; --j) {
            a->data_list[j+1] = a->data_list[j];
        }
        a->data_list[j + 1] = key;
    }
}
// 希尔排序
void shell_sort(array * a){
    int m = a->length;
    do {
        m = m / 3 + 1;
        for (int i = m + 1; i <= a->length; ++i) {
            if (a->data_list[i] < a->data_list[i - m]){
                int key = a->data_list[i],j;
                for (j = i - m;j >= 0 &&key < a->data_list[j] ; j-=m) {
                    a->data_list[j + m] = a->data_list[j];
                }
                a->data_list[j+m] = key;
            }
        }
    }while (m > 1);
}
// 堆排序
void build_heap(array * a,int root,int length){
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int max_id = root;
    if (left < length && a->data_list[left] > a->data_list[max_id]) max_id = left;
    if (right < length && a->data_list[right] > a->data_list[max_id]) max_id = right;
    if (max_id != root){
        swap_array(a,max_id,root);
        build_heap(a,max_id,length);
    }
}
void heap_sort(array * a){
    int i;
    for (i = a->length / 2 - 1; i >= 0 ; --i) {
        build_heap(a,i,a->length);
    }
    for (i = a->length - 1; i >= 1 ; --i) {
        swap_array(a,0,i);
        build_heap(a,0,i);
    }
}
// 快速排序
void q_sort(element_type *a, int s, int e) {
    if (s >= e) return;
     int i = s, j = e, k = a[s];
     do {
         while (i < j && k <= a[j]) --j;
            a[i] = a[j];
         while (i < j &&  k >= a[i]) ++i;
            a[j] = a[i];
     } while (i < j);
     a[i] = k;
     q_sort(a, s, i - 1);
     q_sort(a, i + 1, e);

}
void quick_sort(array * a){
    q_sort(a->data_list, 0, a->length - 1);
}
//桶排序
void bucket_sort(array * a){
    int key = a->data_list[0];
    for (int i = 0; i < a->length; ++i) {
        if (a->data_list[i] > key){
            key = a->data_list[i];
        }
    }
    int bucket_size = key + 1;
    int bucket[bucket_size];
    for (int i = 0; i < bucket_size; ++i) {
        bucket[i] = 0;
    }
    for (int i = 0; i < a->length; ++i) {
        bucket[a->data_list[i]]++;
    }
    for (int i = 0,j = 0; i < bucket_size; ++i) {
        while (bucket[i] != 0){
            a->data_list[j] = i;
            j++;
            bucket[i]--;
        }
    }
}
// 归并排序
#define SORT_LEN 64
void sort_(element_type e[],int start,int mid,int last){
    element_type t[SORT_LEN];
    int i = start,j = mid + 1,k = 0;
    while (i <= mid && j <= last){
        if (e[i] < e[j])
            t[k++] = e[i++];
        else
            t[k++] = e[j++];
    }
    if (j == last + 1) {
        while (i <= mid) {
            t[k++] = e[i++];
        }
    }
    if (i == mid + 1) {
        while (j <= last) {
            t[k++] = e[j++];
        }
    }
    i = start;
    for (int l = 0; l < k;++l, ++i) {
        e[i] = t[l];
    }
}
void m_sort(element_type e[],int start,int last){
    if (start >= last) return;
    int mid = (last + start) / 2;
    m_sort(e,start,mid);
    m_sort(e,mid + 1,last);
    sort_(e,start,mid,last);
}
void merge_sort(array * a){
    m_sort(a->data_list,0,a->length - 1);
}
// 直接查找
element_type goto_search(array * a,element_type key){
    int i = 0;
    while (key != a->data_list[i++]);
    if (i != a->length)
        return i;
    return -1;
}
// 折半查找
element_type binary_search(array * a,element_type key){
    int low ,high,mid;
    low = 0;
    high = a->length - 1;
    while (low <= high){
        mid = (low + high)/2;
        if (key < a->data_list[mid])
            high = mid - 1;
        if (key > a->data_list[mid])
            low = mid + 1;
        else
            return low;
    }
    return -1;
}
// 重写标准库排序
void my_swap(void * dest,void * src,size_t size_){
    char temp[size_];
    memcpy(temp,dest,size_);
    memcpy(dest,src,size_);
    memcpy(src,temp,size_);
}
void my_sort(void * base ,size_t length ,size_t size_,int (*cmp)(const void *,const void *)){
    if (length <= 1) return;
    char * pivot = base;
    size_t low = 0;
    size_t high = length - 1;
    while (low < high){
        if (cmp((char *)(base + low * size_),pivot) < 0 ) low++;
        else if (cmp((char *)(base + high * size_) ,pivot) > 0) high--;
        else my_swap((char *)(base + low * size_),(char *)(base + high * size_),size_);
    }
    my_sort(base,high,size_,cmp);
    my_sort((char *)(base + (high + 1)* size_),length - high - 1,size_,cmp);
}
#endif //UNTITLED1_ARRAY_H
