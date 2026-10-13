#include "sort.h"

/*
  Нийлүүлэн эрэмбэлэх аргын цааш хуваагдах ёсгүй хэмжээ
 */
#define CUTOFF 10

/*
  a, b хаяганд хадгалагдсан сурагчдыг нэрээр жиших функц.
  a->name, b->name-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.
  
*/
int nereer(const Student *a, const Student *b)
{
        return strcmp(a->name, b->name) < 0;
}

/*
  a, b хаяганд хадгалагдсан сурагчдыг насаар нь жиших функц.
  a->age, b->age-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.
*/
int nasaar(const Student *a, const Student *b)
{
	if(a->age < b->age){
		return 1;
	}
	if(a->age > b->age){
		return -1;
	}
	return 0;

}
	
/*
  a, b хаяганд хадгалагдсан сурагчдыг голчоор  нь жиших функц.
  a->gpa, b->gpa-ээс их бол -1, тэнцүү бол 0, бага бол 1-ийг буцаана.  
*/
int golchoor(const Student *a, const Student *b)
{
        if(a->gpa > b->gpa){
			return -1;
		}
		if(a->gpa < b->gpa){
			return 1;
		}
		return 0;
	
}


/*
  Оруулан эрэмбэлэх функц.
  Жиших үйлдлийг less функцэн заагчийг ашиглан хийнэ.
  Уг функц нь эрэмбэлэхдээ a хүснэгтийн lo-оос
  hi завсыг л зөвхөн эрэмбэлнэ.
*/
void insertion_sort(Student a[],
                    int lo, int hi,
                    int (*less)(const Student *, const Student *))
{
        for (int i = lo + 1; i <= hi; i++) {
        Student current = a[i];
        int j;

        for (j = i - 1; j >= lo; j--) {
            if (less(&current, &a[j]) > 0) {
                a[j + 1] = a[j];
            } else {
                break;
            }
        }

        a[j + 1] = current;
    }
}

/*
  Нийлүүлсэн эрэмбэлэх аргын mege үйлдэл.
  Уг функц нь a хүснэгтэд [lo; mid], [mid+1; hi] завсарт
  эрэмбэлэгдсэн хүснэгтийг нийлүүлэн [lo; hi] завсарт эрэмбэлэгдсэн хүснэгт болгоно.
  aux хүснэгт нь нэмэлтээр ашиглах хүснэгт. Оюутнуудыг хооронд нь жишихдээ less функцэн
  заагчийг ашиглана.
*/
void merge(Student a[],
           Student aux[],
           int lo,
           int mid,
           int hi,
           int (*less)(const Student *, const Student *))
{
        for (int k = lo; k <= hi; k++) {
        aux[k] = a[k];
    }

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++) {
        if (i > mid) {
            a[k] = aux[j];
            j++;
        } else if (j > hi) {
            a[k] = aux[i];
            i++;
        } else if (less(&aux[j], &aux[i]) > 0) {
            a[k] = aux[j];
            j++;
        } else {
            /* Тэнцүү бол зүүн талын элементийг эхэлж авна. */
            a[k] = aux[i];
            i++;
        }
    }
}


/*
  Нийлүүлсэн эрэмбэлэх функц.
  hi - lo <= CUTOFF бол оруулан эрэмбэлэх аргыг хэрэглэнэ.
  Жиших үйлдлийг less функцэн заагчийг ашиглан хийнэ.
  Уг функц нь merge, insertion_sort функцүүдийг дуудан ашиглах ёстой.
*/
void mergesort(Student a[],
               Student aux[],
               int lo,
               int hi,
               int (*less)(const Student *, const Student *))
{
        if (lo >= hi) {
        return;
    }

    if (hi - lo <= CUTOFF) {
        insertion_sort(a, lo, hi, less);
        return;
    }

    int mid = lo + (hi - lo) / 2;

    mergesort(a, aux, lo, mid, less);
    mergesort(a, aux, mid + 1, hi, less);

    if (less(&a[mid + 1], &a[mid]) <= 0) {
        return;
    }

    merge(a, aux, lo, mid, hi, less); 
}
