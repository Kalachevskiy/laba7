#include <iostream>
#include <locale>
using namespace std;
//Информация о временном промежутке в пределах одного дня
//(учитывать часы, минуты секунды)

//Часть А 
struct MyTime
{
	int seconds = 0;
	int minutes = 0;
	int hours = 1;
};
struct MyInterval
{
	MyTime startTime;
	MyTime endTime;
	int difference{ endTime.hours * 3600 + endTime.minutes * 60 + endTime.seconds - startTime.hours * 3600 - startTime.minutes * 60 - startTime.seconds };
};
MyTime SetTime(int hours, int minutes, int seconds)
{
	MyTime time{ time.hours = 0, time.minutes = 0, time.seconds = 0 };
	if (seconds < 60)
		time.seconds = seconds;
	else
	{
		time.minutes = seconds / 60;
		time.seconds = seconds % 60;
	}
	if (minutes < 60)
		time.minutes += minutes;
	else
	{
		time.hours = minutes / 60;
		time.minutes += minutes % 60;
	}
	time.hours += hours;
	return time;
}
void SetSeconds(MyTime time, int seconds)
{
	time.seconds = seconds;
}
void SetMinutes(MyTime time, int minutes)
{
	time.minutes = minutes;
}
void SetHours(MyTime time, int hours)
{
	time.hours = hours;
}
void ShowTime(MyTime time)
{
	cout << time.hours << ":" << time.minutes << ":" << time.seconds << endl;
}
MyInterval* SetInterval(MyInterval* interval, MyTime startTime, MyTime endTime)
{
	interval->startTime = startTime;
	interval->endTime = endTime;
	interval->difference = endTime.hours * 3600 + endTime.minutes * 60 + endTime.seconds - startTime.hours * 3600 - startTime.minutes * 60 - startTime.seconds;
	return interval;
}

//Структура данных «односвязный список – очередь».
//Сгруппировать интервалы времени, длительность которых равна
//между собой.
//Часть B
struct List
{
	MyInterval interval;
	List* next;
};
List* QCreate(MyInterval interval)
{
	List* temp = new List;
	temp->interval = interval;
	temp->next = NULL;
	return temp;
}

//Работает только если присваивать head (передавать по  ссылке ??), не работает без присваивания
List* QPush(List*& head, MyInterval interval)
{
	List* item = new List;
	item->interval = interval;
	item->next = head;
	head = item;
	return head;
}
MyInterval QPop(List*& head, MyInterval interval)
{
	List* curr = head;
	List* prev = curr;
	while (curr->next != NULL)
	{
		prev = curr;
		curr = curr->next;
	}
	MyInterval temp = curr->interval;
	prev->next = NULL;
	delete curr;
	return temp;
}
void PrintList(List* head)
{
	List* curr = head;
	int counter = 0;
	do
	{
		counter++;
		cout << "Element #" << counter << "\nfrom ";
		ShowTime(curr->interval.startTime);
		cout << "to ";
		ShowTime(curr->interval.endTime);
		cout << "Difference (seconds): " << curr->interval.difference << endl;
		curr = curr->next;
	} while (curr->next != NULL);
}
void Group(List* head)
{
	int grouppedElements = 0;
	List* currElement = head;
	MyInterval value = currElement->interval;
	List* newList = QCreate(head->interval);
	while (currElement->next != NULL)
	{
		currElement = currElement->next;
		if (currElement->interval.difference == value.difference)
		{
			QPush(newList, currElement->interval);
			grouppedElements++;
		}
		if (currElement->next == NULL)
		{
			currElement = head;
			value = currElement->interval;
			for (int i = 0; i < grouppedElements; i++)
			{
				currElement = currElement->next;
			}
		}
	}
	head = newList;
}
int main()
{
	MyTime time2 = SetTime(2, 0, 0);
	ShowTime(time2);
	MyTime time1;// = SetTime(1, 0, 0);
	ShowTime(time1);
	MyInterval interval{ interval.startTime = time1, interval.endTime = time2 };
	List* list = QCreate(interval);
	QPush(list, interval);
	PrintList(list);
}