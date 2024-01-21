#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

void populateArr(vector<int> *, int);
void printVector(vector<int> *);
void bubbleSort(vector<int> *, SDL_Renderer *);
void drawState(vector<int> *, SDL_Renderer *, int, int);

int main() {
    vector<int> arr;

    // create a render window using SDL
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_CreateWindowAndRenderer(
        100*10, 100*10, 0,
        &window, &renderer);
    SDL_RenderSetScale(renderer, 10, 10);

    populateArr(&arr, 100);
    //printVector(&arr);
    bubbleSort(&arr, renderer);
    //printVector(&arr);
}

void populateArr(vector<int> * arr, int elements) {
    for(int i=0; i<elements; i++) {
        // populate with numbers in the range of 1 to 99
        (*arr).push_back(rand() % 99 + 1);
    }
}

void printVector(vector<int> * arr) {
    cout << "vector contains : ";
    for(int i : *arr) {
        cout << i << " ";
    }
    cout << "\n";
}

void bubbleSort(vector<int> * arr, SDL_Renderer * renderer) {
    bool sorted = false;
    while(sorted == false) {
        sorted = true;
        for(int i=0; i<((int) (*arr).size())-1; i++) {
            if((*arr)[i]>(*arr)[i+1]) {
                // swap elements
                swap((*arr)[i], (*arr)[i+1]);
                sorted = false;
            }
            // clear screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            // draw new state
            drawState(arr, renderer, i, i+1);
            // present window
            SDL_RenderPresent(renderer);
            // delay
            SDL_Delay(6);
        }
    }
}

void drawState(vector<int> * arr, SDL_Renderer * renderer, int pre, int post) {
    int index = 0;
    for(int i : *arr) {
        if(index == pre)
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        else if(index == post)
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index++;
    }
}
