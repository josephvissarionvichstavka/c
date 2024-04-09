//
// Created by father on 2024/4/9.
//

#ifndef UNTITLED1_ARRAY_H
#define UNTITLED1_ARRAY_H
typedef int element_type ;// ����Ԫ������
typedef short int status; //
#define  true 1
#define false 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//  ���鶨��
const int size = 16;
#ifndef KKK  // �Ƿ��ǿɱ�����
typedef struct {// �ɱ䳤
    element_type * data_list; // ���������
    int length;// �������
    int size;// ���������С
} array ;
#else
typedef struct {// ���ɱ䳤
    element_type data_list[size]; // ���������
    int length;// �������
    int size;// ���������С
} array ;
#endif
// �������� ����
void init_array(array * a){
#ifndef KKK
    a->data_list = malloc(sizeof(element_type) * size); // ����ռ�
    if (a->data_list == 0){
        fprintf(stderr,"����ʧ��");
        exit(-1);
    }
#endif
    a->size = size;
    a->length = 0;
}
#ifndef KKK
// �������飬ָ������
void init_array_size(array * a,int size_){
    a->data_list = malloc(sizeof(element_type) * size_);
    if (a->data_list == 0){
        fprintf(stderr,"����ʧ��");
        exit(-1);
    }
    a->length = 0;
    a->size = size_;
}
// �������飬ָ�����ȣ�ȫ����0
void init_array_size_0(array * a,int size_){
    a->data_list = malloc(sizeof(element_type) * size_);
    if (a->data_list == 0){
        fprintf(stderr,"����ʧ��");
        exit(-1);
    }
    a->length = size_;
    a->size = size_;
    for (int i = 0; i < size_; ++i) {
        a->data_list[i] = 0;
    }
}
// �������飬ָ�����ȣ�ȫ����e
void init_array_size_(array * a,int size_,element_type e){
    a->data_list = malloc(sizeof(element_type) * size_);
    if (a->data_list == 0){
        fprintf(stderr,"����ʧ��");
        exit(-1);
    }
    a->length = size_;
    a->size = size_;
    for (int i = 0; i < size_; ++i) {
        memcpy(&a->data_list[i],&e,sizeof(element_type));
    }
}
// ��ֵ����
void init_array_(array * a,const element_type * begin,const element_type * end){
    int length = end - begin + 1; // ����ָ��֮��ļ���  intһ�μ�4���ֽ� +1 ������ĳ���
    a->data_list = malloc(sizeof(element_type) * length);
    if (a->data_list == 0){
        fprintf(stderr,"����ʧ��");
        exit(-1);
    }
    memcpy(a->data_list,begin,length * sizeof(element_type));
    a->length = length;
    a->size = length;
}
// ������ֵ
void init_array_copy(array * a,const array * b){
    a->data_list = malloc(sizeof(element_type) * b->size);
    if (a->data_list == 0){
        fprintf(stderr,"����ʧ��");
        exit(-1);
    }
    memcpy(a->data_list,b->data_list,sizeof(element_type) * b->size); // ���ٺ�b��ͬ�Ŀռ�
    a->size = b->size;
    a->length = b->length;
}
#endif
// ���ٺ���
void destroy_array(array * a){
#ifndef KKK
    free(a->data_list); // �ͷ�����Ŀռ�
#endif
    a->length = a->size = 0; // ��ֹ����
}
// �ж������Ƿ�Ϊ��
status empty_array(array a){
    if (a.data_list == 0 || a.size == 0){ // ������ܲ�����
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    if (a.length == 0)
        return true;
    return false;
}
// �ж������Ƿ�����
status fall_array(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    if (a.length == a.size)
        return true;
    return false;
}
// �����С
size_t size_array(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    return a.size;
}
// ��������ʣ��ռ�
size_t capacity(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    return a.size - a.length;
}
//  ���������� ���
void swap_array(array * a,int i,int j){
    element_type temp;
    memcpy(&temp,&a->data_list[i],sizeof(element_type));
    memcpy(&a->data_list[i],&a->data_list[j],sizeof(element_type));
    memcpy(&a->data_list[j],&temp,sizeof(element_type));
}
// ���·���ռ�
status reserve(array * a,int size_){
    if (size_ > a->size){
        element_type * new = realloc(a->data_list,size_ * sizeof(element_type));
        if (new == 0){
            fprintf(stderr,"����ʧ��");
            exit(-1);
        }
        a->data_list = new;
        a->size = size_;
        return true;
    }
    return false;
}
// ��С�ռ�
status reserve_(array * a){
    if (a->length < a->size / 4){
        element_type * new = realloc(a->data_list,a->size / 4);
        if (new == 0){
            fprintf(stderr,"����ʧ��");
            exit(-1);
        }
        a->data_list = new;
        a->size /= 2;
        return true;
    }
    return false;
}
// ����
status insert_array(array * a,element_type e,int i){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    if (a->length + 1 > a->size){
#ifndef KKK
        reserve(a,a->size*2);
#else
        fprintf(stderr,"�������޷�����"); // ���������޷�����
        return false;
#endif
    }
    if (i > a->length){
        fprintf(stderr,"������Խ��");
        return false;
    }
    for (int j = a->length; j > i; --j) {
        memcpy(&a->data_list[j + 1],&a->data_list[j],sizeof(element_type));
    }
    memcpy(&a->data_list[i],&e,sizeof(element_type));
    a->length++;
    return true;
}
// ��һ�������begin��end��������
status insert_array_itc(array * a,const element_type * begin,const element_type * end){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    int length = end - begin + 1;
    if (a->length + length > a->size){
#ifndef KKK
        reserve(a,a->size*2);
#else
        fprintf(stderr,"�������޷�����");
        return false;
#endif
    }
    for (int i = 0; i < length; ++i) {
        memcpy(&a->data_list[a->length++],begin++,sizeof(element_type));
    }
    a->length+= length;
    return true;
}
// ��һ��������±�begin��end��������
status insert_array_at(array * a,element_type e,int begin,int end){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    if (begin >= end){
        fprintf(stderr,"������Ч");
        exit(-1);
    }
    if (a->length + end - begin > a->size){
#ifndef KKK
        reserve(a,a->size*2);
#else
        fprintf(stderr,"�������޷�����");
        return false;
#endif
    }
    if (begin > a->length || end > a->size){
        fprintf(stderr,"������Խ��");
        return false;
    }
    for (int j = a->length; j > end; --j) {// �ֳ����ֿռ�
        memcpy(&a->data_list[j + 1],&a->data_list[j],sizeof(element_type));
    }
    for (int i = begin; i < end; ++i) { //���帳ֵ
        memcpy(&a->data_list[i],&e,sizeof(element_type));
    }
    a->length += (end - begin);
    return true;
}
// β��
status insert_array_end(array * a,element_type e){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    if (a->length + 1 >= a->size){
#ifndef KKK
        reserve(a,a->size * 2);
#else
        fprintf(stderr,"�������޷�����");
        return false;
#endif
    }
    memcpy(&a->data_list[a->length],&e,sizeof(element_type));
    a->length++;
    return true;
}
// ɾ��
status delete_array(array * a,element_type * e,int i) {
    if (a->data_list == 0 || a->size == 0) {
        fprintf(stderr, "�����鲻����");
        exit(-1);
    }
    if (empty_array(*a)) {
        fprintf(stderr, "������Ϊ��");
        return false;
    }
    if (i >= a->length) {
        fprintf(stderr, "������Խ��");
        return false;
    }
    memcpy(&e, &a->data_list[i], sizeof(element_type));
    for (int j = i; j < a->length; ++j) {
        memcpy(&a->data_list[j], &a->data_list[j + 1], sizeof(element_type));
    }
    a->length--;
    return true;
}
// βɾ
status delete_array_end(array * a,element_type * e){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    if (empty_array(*a)){
        fprintf(stderr,"������Ϊ��");
        return false;
    }
    memcpy(&e,&a->data_list[a->length - 1],sizeof(element_type));
    a->length--;
    return true;
}
// ɾ������
status delete_array_all(array * a,int start,int end){
    if (a->data_list == 0 || a->size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    if (empty_array(*a)){
        fprintf(stderr,"������Ϊ��");
        return false;
    }
    if (start >= a->length || end >= a->length){
        fprintf(stderr,"������Խ��");
        return false;
    }
    for (int i = start,j = end; i != end; ++i,++j) {
        memcpy(&a->data_list[i],&a->data_list[j],sizeof(element_type));
    }
    a->length -= (end - start);
    reserve_(a);
    return true;
}
//���
void clean_array(array * a){
    a->length = 0;
    reserve_(a);
}
// �������鳤��
size_t array_length(array a){
    if (a.data_list == 0 || a.size == 0){
        fprintf(stderr,"�����鲻����");
        exit(-1);
    }
    return a.length;
}
// ���·���ռ�
void resize_array(array * a,int size_){
    if (size_ > a->size){
        reserve(a,size_);
    } else {
        reserve_(a);
    }
}
// �����ײ�
element_type * fount(array * a){
    return &a->data_list[0];
}
// ����β��
element_type * back(array * a){
    return &a->data_list[a->length - 1];
}
// α�±����
element_type at_array(array * a,int i){
    if (i > a->length){
        fprintf(stderr,"Խ��");
        return false;
    }
    return a->data_list[i];
}
// Ѱ��Ԫ�� ����ҵ������±�
int find_by_array(array * a, element_type e,int (*compare)(const element_type *,const element_type *)){
    for (int i = 0; i < a->length; ++i) {
        if (compare(&a->data_list[i],&e)){
            return i;
        }
    }
    return -1;
}
// ����Ƚ�
status compare(const array * a1,const array * a2){
    if (a1->size != a2->size || a1->length != a2->length) return false;
    for (int i = 0; i < a1->length; ++i) {
        if (a1->data_list[i] != a2->data_list[i]) return false;
    }
    return true;
}
// ���鲻���
status not_compare(const array * a1,const array * a2){
    if (a1->size != a2->size || a1->length != a2->length) return true;
    for (int i = 0; i < a1->length; ++i) {
        if (a1->data_list[i] != a2->data_list[i]) return true;
    }
    return false;
}
// ��������
void sort_array(array * a,int (*cmp)(const element_type *,const element_type *)){
    qsort(a->data_list, a->length, sizeof(element_type), (int (*)(const void *, const void *)) cmp);
}
// ���鲿������
void sort_array_begin_and_end(array * a,int begin,int end,int (*cmp)(const element_type *,const element_type *)){
    qsort(&a->data_list[begin], end - begin, sizeof(element_type), (int (*)(const void *, const void *)) cmp);
}
// ð������
void bullet_sort(array * a){
    for (int i = 0; i < a->length - 1; ++i) {
        for (int j = 0; j < a->length - 1 - i; ++j) {
            if (a->data_list[j] > a->data_list[j + 1]){
                swap_array(a,j,j+1);
            }
        }
    }
}
// ѡ������
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
// ��������
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
// ϣ������
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
// ������
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
// ��������
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
//Ͱ����
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
// �鲢����
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
// ֱ�Ӳ���
element_type goto_search(array * a,element_type key){
    int i = 0;
    while (key != a->data_list[i++]);
    if (i != a->length)
        return i;
    return -1;
}
// �۰����
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
// ��д��׼������
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
