#include <iostream>
#include <windows.h>
#include <algorithm>
#include <random>
using namespace std;

class Vector {
	unsigned int capacity = 10; // при створенні масиву, він одразу для себе робить запас пам'яті на 10 елементів
	int* data = new int[capacity];
	unsigned int length = 0; // фактична (реальна) кількість елементів, присутніх у масиві

public:
	Vector() {}

	void AddToBack(int value) {
		if (length < capacity) // якщо виділенної зарання пам'яті ВИСТАЧАЄ для додавання чергового елемента
			data[length] = value;
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			// в новий масив в кінець (по індексу 10) пишеться ОДИНАДЦЯТИЙ елемент
			temp[length] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	void AddToFront(int value) {
		if (length < capacity) { // ще є вільна пам'ять під черговий елмент
			// перевиділяти пам'ять на 1 елемент кожен раз - погана ідея (якщо елементів буде більше ніж 300000+ то все буде відбуватися максимально повільно)
			// при тому що пам'ять вже виділена (є кепесіті), то доведеться зробити зсув для всіх існуючих елементів на 1 вправо
			for (int i = length - 1; i >= 0; i--) { // зсув іде справа наліво (тому що якщо робити його зліва направо, з початку масива в кінець) то можна втратити існуючі елементи
				data[i + 1] = data[i];
			}
			data[0] = value;
		}
		else { // АЛЕ ЯКЩО МІСЦЯ ВЖЕ НЕ ВИСТАЧАЄ, ТО
			// треба перевиділити пам'ять
			capacity *= 2; // збільшуємо запас пам'яті у 2 рази (можна і в 1.5, можна і в 1.2)
			// якщо був запас 10 елементів, то стане 20
			// якщо запас був 20 елементів, то стане 40, і тд
			int* temp = new int[capacity]; // новий масив буде в 2 рази більше по пам'яті
			// але в старому масиві все ще усього 10 елементів, тому цикл треба написати так, щоб зачепити лише старі елементі зі старого масиву
			for (int i = 0; i < length; i++) {
				temp[i + 1] = data[i];
			}
			// в новий масив в початок (по індексу 0) пишеться ОДИНАДЦЯТИЙ елемент
			temp[0] = value;
			delete[] data; // в цілях запобігання витокам пам'яті, чистимо пам'ять від старого масиву
			data = temp; // переставляємо покажчик на новий масив
		}
		length++;
	}

	void RemoveFromBack() {
		if (length == 0) {
			cout << "масив пустий, видаляти НЕМА ЧОГО!\n";
			return;
		}
		length--;
	}

	// написати:
	// RemoveFromFront() - метод видаляє значення по індексу 0
	// Insert(value, index) - метод який вставляє значення по індексу без втрати елемента по індексу
	// RemoveByIndex(index) - метод видаляє елемент по індексу
	// RemoveByValue(value) - метод видаляє всі вказані значення з масиву
	// Sort() - метод сортує масив за зростанням
	// Reverse() - метод змінює порядок слідуанн елементів на протилежний
	// Shuffle() - метод випадковим чином перемішує елементи в масиві

	void RemoveFromFront() {
		if (length == 0) {
			cout << "massif empty\n";
			return;
		}
		for (int i = 0; i < length - 1; i++) {
			data[i] = data[i + 1];
		}
		length--;
	}

	void Insert(int value, int index) {
		if (index > length) {
			return;
		}
		if (length >= capacity) {
			capacity *= 2;
			int* temp = new int[capacity];
			for (int i = 0; i < length; i++) {
				temp[i] = data[i];
			}
			delete[] data;
			data = temp;
		}
		for (int i = length - 1; i >= index; i--) {
			data[i + 1] = data[i];
		}
		data[index] = value;
		length++;
	}

	void RemoveByIndex(int index) {
		if (index < 0 || index >= length) {
			cout << "Error\n";
			return;
		}
		for (int i = index; i < length - 1; i++) {
			data[i] = data[i + 1];
		}
		length--;
	}
	
	void RemoveByValue(int value) {
		int i = 0;
		while (i < length) {
			if (data[i] == value) {
				for (int j = i; j < length - 1; j++) {
					data[j] = data[j + 1];
				}
				length--;
			}
			else {
				i++;
			}
		}
	}

	void Sort() {
		if (length == 0) {
			cout << "massif empty\n";
			return;
		}
		sort(data, data + length);
	}

	void Reverse() {
		if (length == 0) {
			cout << "massif empty\n";
			return;
		}
		reverse(data, data + length);
	}

	void Shuffle() {
		if (length == 0) {
			cout << "massif empty\n";
			return;
		}
		random_device rd;
		mt19937 g(rd());
		shuffle(data, data + length, g);
	}

	friend ostream& operator<<(ostream& os, const Vector& vec);
	int& operator[](int index);
	bool operator==(const Vector& other) const;
	bool operator!=(const Vector& other) const;

	void Print() const {
		if (length == 0) {
			cout << "масив пустий!\n";
		}
		else {
			cout << "ємність масиву: " << capacity << "\n";
			cout << "елементи масиву: ";
			for (int i = 0; i < length; i++)
			{
				cout << data[i] << " ";
			}
			cout << "\n";
		}
	}

	~Vector() {
		cout << "D-TOR\n";
		if (data != nullptr) {
			delete[] data;
		}
	}

	Vector(const Vector& original) {
		cout << "COPY C-TOR\n";
		this->length = original.length;
		this->capacity = original.capacity;
		this->data = new int[capacity];
		for (int i = 0; i < length; i++)
			this->data[i] = original.data[i];
	}
};

ostream& operator<<(ostream& os, const Vector& vec) {
	for (unsigned int i = 0; i < vec.length; i++) {
		os << vec.data[i] << " ";
	}
	return os;
}
istream& operator >> (istream& is, Vector& vec) {
	int value;
	cin >> value;
	vec.AddToBack(value);
	return is;
}
int& Vector:: operator[](int index) {
	return data[index];
}
bool Vector::operator ==(const Vector& other)  const {
	if (length != other.length) return false;
	for (unsigned int i = 0; i < length; i++) {
		if (data[i] != other.data[i]) return false;
	}
	return true;
}
bool Vector::operator!=(const Vector& other) const {
	return !(*this == other); 
}


int main() {
	SetConsoleOutputCP(1251);
	srand(time(0));

	Vector a;

	a.AddToBack(10);
	a.AddToBack(5);
	a.AddToBack(30);

	a.Print();

	// a.RemoveFromFront();
	// a.Insert(29, 1);
	// a.RemoveByIndex(1);
	// a.RemoveByValue(10);
	// a.Sort();
	// a.Reverse();
	// a.Shuffle();

	a.Print();

	Vector b = a; 

	cout << "Вміст a:\n";
	cout << a; 
	cout << "a[1] = " << a[1] << "\n";  
	a[1] = 34; 
	cout << "Новий a[1] = " << a[1] << "\n";
	if (a == b) {
		cout << "a і b однакові\n";
	}
	else {
		cout << "a і b різні\n";
	}

	if (a != b) {
		cout << "a і b різні\n";
	}
	else {
		cout << "a i b однакові\n";
	}

	
}

