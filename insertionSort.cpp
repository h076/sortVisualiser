#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void populateArr(vector<int> *, int);
void printVector(vector<int> *);
void insertionSort(vector<int> *, SDL_Renderer *);
void drawState(vector<int> *, SDL_Renderer *, int, int);
bool checkSort(vector<int> *, SDL_Renderer *);
void drawCheck(vector<int> *, SDL_Renderer *, int, bool);

int main() {
    vector<int> arr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "ERROR: " << SDL_GetError() << "\n";
		return 1;
	}

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    // initialise window
	SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr) {
		cout << "ERROR: can't create window: " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

    // initialise renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == nullptr) {
		cout << "ERROR: can't create renderer: " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

    // populate vector with 100 values
    populateArr(&arr, 100);

    // set render scale
    SDL_RenderSetScale(renderer, 8, 8);

    printVector(&arr);

    bool sorted = false;
    int running = 1;
    while(running && !sorted) {
       SDL_Event event;
       while(SDL_PollEvent(&event)) {
           switch(event.type) {
               case SDL_QUIT:
                   running = 0;
                   break;
           }
       }

       SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
       SDL_RenderClear(renderer);

       insertionSort(&arr, renderer);
       sorted = checkSort(&arr, renderer);
    }

    printVector(&arr);

    //SDL_Quit();

    return 0;
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

void insertionSort(vector<int> * arr, SDL_Renderer * renderer) {
    int key, j;
    for(int i=0; i<(*arr).size(); i++) {
        j = i-1;
        key = (*arr)[i];
        while(j>=0 && (*arr)[j]>key) {
            (*arr)[j+1] = (*arr)[j];
            j--;
        }
        (*arr)[j+1] = key;

        // clear window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // draw sort state
        drawState(arr, renderer, i, j);

        // present render
        SDL_RenderPresent(renderer);

        //Delay
        SDL_Delay(50);
    }
}

bool checkSort(vector<int> * arr, SDL_Renderer * renderer) {
    int prev = (*arr)[0];
    bool sorted = true;
    for(int i=0; i<(*arr).size(); i++) {
        //clear window
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        if((*arr)[i] < prev) {
            sorted = false;
            drawCheck(arr, renderer, i, !sorted);
        }else {
            drawCheck(arr, renderer, i, !sorted);
        }

        // present render
        SDL_RenderPresent(renderer);

        // delay
        SDL_Delay(50);
    }
    return sorted;
}

void drawState(vector<int> * arr, SDL_Renderer * renderer, int pre, int post) {
    int index = 0;
    for(int i : *arr) {
        if(index == pre) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }else if(index == post) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }else {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(renderer, index, 99, index, i);
        index++;
    }
}

void drawCheck(vector<int> * arr, SDL_Renderer * renderer, int check, bool error) {
   int index = 0;
   for(int i : *arr) {
       SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
       if(index == check && error) {
           SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
       }else if(index > check) {
           SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
       }
       SDL_RenderDrawLine(renderer, index, 99, index, i);
       index++;
   }
}
