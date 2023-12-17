#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

vector<vector<char>> maze;
vector<vector<int>> visited;
int rows;
int cols;
int start_row;
int start_col;

enum terrain
{
  empty,
  wall,
  goal,
  crumb
};

void get_maze(char *file_name)
{
  char c;
  char rows_s[3] = {'\0'};
  char cols_s[3] = {'\0'};
  int rows_i = 0;
  int cols_i = 0;
  int swap = 0;
  bool flag = 0;
  
  string myText;
  
  ifstream maze_file;
  maze_file.open(file_name);
  while ((getline(maze_file, myText)))
  {
    for (int i = 0; i < myText.size(); i++)
    {
      if (myText[i] == '\n')
      {
        flag = 1;
        break;
      }
      else if (myText[i] == ',')
      {
        swap = 1;
      }
      else if (!swap)
      {
        rows_s[rows_i] = myText[i];
        rows_i++;
      }
      else
      {
        cols_s[cols_i] = myText[i];
        cols_i++;
      }
    }
    if (flag == 1)
    {
      break;
    }
  }
  rows = atoi(rows_s);
  cols = atoi(cols_s);
  
  string token;
  
  while (!maze_file.eof())
  {
    std::getline(maze_file, token);
    vector<char> vecRow;
    vecRow.assign(token.begin(), token.end());
    maze.push_back(vecRow);
  }
  
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols + 1; j++)
    {
      if (maze[i][j] == 's')
      {
        start_row = i;
        start_col = j;
        cout << "start_row " << start_row << endl << "start_col " << start_col << endl;  
      }
      if (maze[i][j] == 'g')
      {
        int end_row = i;
        int end_col = j;
        cout << "end_row " << end_row << endl << "end_col " << end_col << endl;
      }
    }
  }
 
  maze_file.close();
}

void print_maze()
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      cout << maze[i][j];
    }
    cout << endl;
    }
  cout << endl;
}

void get_visited()
{
  int x;
  for (int i = 0; i < rows; ++i)
  {
    vector<int> vecRow;
    for (int j = 0; j < cols; ++j)
    {
      if (maze[i][j] == '+')
      {
        vecRow.push_back(wall);
      }
      else if (maze[i][j] == 'g')
      {
        vecRow.push_back(goal);
      }
      else
      {
        vecRow.push_back(empty);
      }
    }
    visited.push_back(vecRow);
  }
}

void print_visited()
{
  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      cout << visited[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void add_crumbs()
{
  for (int i = 0; i < rows; ++i)
  {
    vector<char> vecRow;
    for (int j = 0; j < cols; ++j)
    {
      if (maze[i][j] != 's' && visited[i][j] == crumb)
      {
        maze[i][j] = '.';
      }
    }
  }
}

int dfs(int row, int col)
{
  if (visited[row][col] == goal)
  {
    return 1;
  }
  
  if (visited[row][col] == empty)
  {
    visited[row][col] = wall;
    
    if (dfs(row, col - 1))
    {
      visited[row][col] = crumb;
      return 1;
    }
    if (dfs(row + 1, col))
    {
      visited[row][col] = crumb;
      return 1;
    }
    if (dfs(row, col + 1))
    {
      visited[row][col] = crumb;
      return 1;
    }
    if (dfs(row - 1, col))
    {
      visited[row][col] = crumb;
      return 1;
    }
  }
  return 0;
}

int main()
{
  char file_name[] = "maze.txt";
  get_maze(file_name);
  print_maze();
  get_visited();
  print_visited();
  dfs(start_row, start_col);
  add_crumbs();
  print_maze();
  cout << "rows " << rows << endl
  << "cols " << cols;
  return 0;
}
