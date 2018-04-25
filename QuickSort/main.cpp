#include <QCoreApplication>

#include <vector>

using namespace std;

void swap(vector<int>& array, int left, int right);
void quickSort(vector<int>& array, int left, int right);
int partition(vector<int>& array, int left, int right);

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    vector<int> sortMe;

    quickSort(sortMe, 0, sortMe.size() - 1);

    sortMe.push_back(1);
    sortMe.push_back(2);
    sortMe.push_back(3);
    sortMe.push_back(4);
    sortMe.push_back(5);
    sortMe.push_back(6);
    sortMe.push_back(7);
    sortMe.push_back(8);
    sortMe.push_back(9);
    sortMe.push_back(10);

    quickSort(sortMe, 0, sortMe.size() - 1);

    sortMe.clear();

    sortMe.push_back(10);
    sortMe.push_back(9);
    sortMe.push_back(8);
    sortMe.push_back(7);
    sortMe.push_back(6);
    sortMe.push_back(5);
    sortMe.push_back(4);
    sortMe.push_back(3);
    sortMe.push_back(2);
    sortMe.push_back(1);


    quickSort(sortMe, 0, sortMe.size() - 1);

    sortMe.clear();

    sortMe.push_back(5);
    sortMe.push_back(10);
    sortMe.push_back(9);
    sortMe.push_back(2);
    sortMe.push_back(8);
    sortMe.push_back(1);
    sortMe.push_back(7);
    sortMe.push_back(4);
    sortMe.push_back(6);
    sortMe.push_back(3);


    quickSort(sortMe, 0, sortMe.size() - 1);
}

void quickSort
(
    vector<int>& array,
    int left,
    int right
)
{
    if (array.size() < 2) // nothing to sort
        return;

    int index = partition(array, left, right);
    if (left < index - 1)
        quickSort(array, left, index - 1);

    if (index < right)
        quickSort(array, index, right);
}

int partition
(
    vector<int>& array,
    int left,
    int right
)
{
    int pivot = array[(left + right) / 2];
    while (left <= right)
    {
        while (array[left] < pivot) left++;

        while (array[right] > pivot) right--;

        if (left <= right)
        {
            swap(array, left, right);
            left++;
            right--;
        }
    }

    return left;
}

void swap
(
    vector<int>& array,
    int left,
    int right
)
{
    if (left != right)
    {
        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;
    }
}
