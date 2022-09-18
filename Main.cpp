#include <iostream>
#include <SFML/Graphics.hpp>
#include <format>
#include <random>
#include <chrono>
#include <vector>
#include <windows.h>

//Displays the grid on screen
void displayGrid(std::vector<std::vector<int>> grid) {
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			std::cout << std::format("|{:^5}", grid[i][j]);

		}

		std::cout << "|" << std::endl;
	}

	std::cout << std::endl;
}

std::vector<std::vector<int>> prepareNextGenGrid(int rowAmnt) {
	std::vector<std::vector<int>> nextGenGrid;

	for (int i = 0; i < rowAmnt; i++) {
		std::vector<int> v;
		nextGenGrid.push_back(v);

	}

	return nextGenGrid;
}

//Populates the grid with randomized 1 (populated) and 0 (unpopulated) values, size of grid is entered by the user
std::vector<std::vector<int>> populateGrid(int rowAmnt, int colAmnt) {
	std::vector<std::vector<int>> grid;

	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed1);
	std::uniform_int_distribution<int> distribution(0, 1);

	for (int i = 0; i < rowAmnt; i++) {
		std::vector<int> v;
		grid.push_back(v);

	}

	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < colAmnt; j++) {
			grid[i].push_back(distribution(generator));

		}
	}
		//Test Case
		/*for (int j = 0; j < 5; j++) {

			if (j == 0) {
				grid[0].push_back(0);
				grid[1].push_back(0);
				grid[2].push_back(1);
				grid[3].push_back(0);

			}

			if (j == 1) {
				grid[0].push_back(1);
				grid[1].push_back(1);
				grid[2].push_back(1);
				grid[3].push_back(0);

			}

			if (j == 2) {
				grid[0].push_back(1);
				grid[1].push_back(0);
				grid[2].push_back(1);
				grid[3].push_back(0);

			}

			if (j == 3) {
				grid[0].push_back(0);
				grid[1].push_back(0);
				grid[2].push_back(0);
				grid[3].push_back(0);

			}

			if (j == 4) {
				grid[0].push_back(0);
				grid[1].push_back(0);
				grid[2].push_back(1);
				grid[3].push_back(1);

			}
		}*/
		
	displayGrid(grid);

	return grid;
}

//Processes the conditions to determine the status of the current cell based on the number of its live neighbooring cells
int processCell(int liveNeighboors, bool isCellAlive) {

	//std::cout << "Live neighboors cells: " << liveNeighboors << std::endl;
	if(isCellAlive) {
		if(liveNeighboors < 2) {
			return 0;

		}

		else if(liveNeighboors == 2 || liveNeighboors == 3) {
			return 1;

		}

		else {
			return 0;

		}
	}

	else {
		if(liveNeighboors == 3) {
			return 1;

		}

		else {
			return 0;

		}
	}
}

int countNeighbooringCellsValue(std::vector<std::vector<int>> grid, int x, int y) {
	int liveNeighboorCellCount{ 0 };

	//std::cout << "i: " << x << " j: " << y << std::endl;

	//Iterate through all neighboors
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			if((i == x && j == y) || (i >= grid.size() || j >= grid[i].size()) || (i < 0 || j < 0))	{
				continue;

			}

			if(grid[i][j] == 1) {
				liveNeighboorCellCount++;

			}
		}
	}

	return liveNeighboorCellCount;
}

void iterateGrid(std::vector<std::vector<int>> grid, std::vector<std::vector<int>> resultGrid, int row, int col) {
	int generationAmnt{ 0 }, generationCounter{ 0 };
	bool isCurrentCellAlive{ false };

	std::cout << "Enter number of generations: " << std::endl;
	std::cin >> generationAmnt;

	while (generationCounter < generationAmnt) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int currentCellNeighboorsAmnt = countNeighbooringCellsValue(grid, i, j);

				resultGrid[i].push_back(processCell(currentCellNeighboorsAmnt, grid[i][j]));

			}
		}

		generationCounter++;
		grid = resultGrid;

		//Clearing the int vectors
		for (int i = 0; i < col; i++) {
			resultGrid[i].clear();

		}

		std::cout << "Current Generation: " << generationCounter << std::endl;

		Sleep(800);
		system("cls");
		displayGrid(grid);
	}
}

int main() {
	int rowAmnt{ 0 }, colAmnt{ 0 };

	std::cout << "Enter row and col amount: ";
	std::cin >> rowAmnt >> colAmnt;
	std::cout << std::endl;

	std::vector<std::vector<int>> grid = populateGrid(rowAmnt, colAmnt);
	std::vector<std::vector<int>> resultGrid = prepareNextGenGrid(rowAmnt);
	iterateGrid(grid, resultGrid, rowAmnt, colAmnt);

	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;

}