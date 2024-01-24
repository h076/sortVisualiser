#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

void populateArr(vector<int> *, int);
void printVector(vector<int> *);
void bubbleSort(vector<int> *, SDL_Renderer *);
bool checkSort(vector<int> *, SDL_Renderer *);
void drawState(vector<int> *, SDL_Renderer *, int, int);
void drawCheck(vector<int> *, SDL_Renderer *, int, bool);

int main() {
    vector<int> arr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "ERROR: " << SDL_GetError() << "\n";
		return 1;
	}

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

	SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(window == nullptr) {
		cout << "ERROR: can't create window: " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == nullptr) {
		cout << "ERROR: can't create renderer: " << SDL_GetError() << "\n";
		return EXIT_FAILURE;
	}

    populateArr(&arr, 100);

    SDL_RenderSetScale(renderer, 8, 8);

    int running = 1;
    bool sorted = false;
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

        bubbleSort(&arr, renderer);
        sorted = checkSort(&arr, renderer);
	}

    //printVector(&arr);

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

void bubbleSort(vector<int> * arr, SDL_Renderer * renderer) {
    bool sorted = false;
    SDL_Renderer * r = renderer;
    while(sorted == false) {
        sorted = true;
        for(int i=0; i<((int) (*arr).size())-1; i++) {
            if((*arr)[i]>(*arr)[i+1]) {
                // swap elements
                swap((*arr)[i], (*arr)[i+1]);
                sorted = false;
            }
            // clear screen
            SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
            SDL_RenderClear(r);
            // draw new state
            drawState(arr, renderer, i, i+1);
            // present window
            SDL_RenderPresent(r);
            // delay
            SDL_Delay(3);
        }
    }
}

bool checkSort(vector<int> * arr, SDL_Renderer * renderer) {
    bool sorted = true;
    SDL_Renderer * r = renderer;
    int prev = (*arr)[0];
    for(int i=0; i<(*arr).size(); i++) {
        //clear screen
        SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
        SDL_RenderClear(r);

        if((*arr)[i] < prev) {
            sorted = false;
            drawCheck(arr, renderer, i, !sorted);
        }else {
            drawCheck(arr, renderer, i, !sorted);
            prev = (*arr)[i];
        }

        // present window
        SDL_RenderPresent(r);

        // Delay
        SDL_Delay(3);
    }
    return sorted;
}

void drawState(vector<int> * arr, SDL_Renderer * renderer, int pre, int post) {
    int index = 0;
    SDL_Renderer * r = renderer;
    for(int i : *arr) {
        if(index == pre)
            SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        else if(index == post)
            SDL_SetRenderDrawColor(r, 0, 0, 255, 255);
        else
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        SDL_RenderDrawLine(r, index, 99, index, i);
        index++;
    }
}

void drawCheck(vector<int> * arr, SDL_Renderer * renderer, int check, bool error) {
    int index = 0;
    SDL_Renderer * r = renderer;
    for(int i : *arr) {
        SDL_SetRenderDrawColor(r, 0, 255, 0, 255);
        if(index == check && error) {
            SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
        }else if(index > check) {
            SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
        }
        SDL_RenderDrawLine(r, index, 99, index, i);
        index++;
    }
}
