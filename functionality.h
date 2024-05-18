/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

 //---Piece Starts to Fall When Game Starts---//

 /////////////////////////////////////////////
 ///*** START CODING YOUR FUNTIONS HERE ***///

void fallingPiece(float& timer, float& delay, int& colorNum, int& delta_x, int& n, int& space, int& level)
{
    void bomb(int i, int colornum);

    if (timer > delay)
    {
        for (int i = 0; i < 4; i++)
        {
            point_2[i][0] = point_1[i][0];
            point_2[i][1] = point_1[i][1];
            if (space != 1)
            {
                point_1[i][1] += 1;
            }
        }

        bool flag = 0;
        int i = 0;
        if (!anamoly(i))
        {

            if (n == 7)
                bomb(i, colorNum);
            if (level != 2)
                delay = 0.3;
            if (n != 7)
            {
                for (int i = 0; i < 4; i++)
                {
                    gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
                    // std::cout<<"y "<<point_2[i][1]<<"\nx "<<point_2[i][0]<<"\n";
                    //  cout << "gg: " << gameGrid[point_2[i][1]][point_2[i][0]] << endl;
                }
            }
            n = rand() % 8;
            delta_x = rand() % 10;
            if (n == 7)
                delay = 0.04;
            colorNum = 1 + rand() % 7;

            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
                //                std::cout<<"x: "<<point_1[i][0]<<"\n";
                //                std::cout<<"y: "<<point_1[i][1]<<"\n";
            }

            // std::cout<<"End\n";
        }
        timer = 0;
    }
}

void levelup(float& totaltime, int& level, float& delay)
{
    if (totaltime > 30)
    {
        level = 2;
        delay = 0.1;
    }
}
void spacebar(int space)
{
    int i, distance_y;
    if (space == 1)
    {
        int max = point_1[0][1];
        for (int i = 1; i < 4; i++)
        {
            if (point_1[i][1] > max)
                max = point_1[i][1];
        }
        distance_y = 19 - max;
        for (int i = 0; i < 4; i++)
        {
            point_1[i][1] += distance_y;
            while (!anamoly())
            {
                for (int i = 0; i < 4; i++)
                    point_1[i][1] -= 1;
            }
        }
    }
}
int gameOver()
{
    for (int j = 0; j < 10; j++)
    {
        if (gameGrid[0][j] != 0)
        {
            std::cout << "Game Over\n";
            return 0;
        }
    }
    return 1;
}
void bomb(int i, int colorNum)
{
    int x, y;
    x = point_1[i][1];
    y = point_1[i][0];
    x--;
    gameGrid[x][y] = colorNum;

    if (y == 0 && (gameGrid[x][y + 1] == 0 && gameGrid[x + 1][y] == 0))
        gameGrid[x][y] = { 0 };
    else if ((y == 0) && (colorNum == gameGrid[x][y + 1] || colorNum == gameGrid[x + 1][y]))
    {
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
                gameGrid[i][j] = { 0 };
    }

    else if ((y == 9) && (gameGrid[x][y - 1] == 0 && gameGrid[x + 1][y] == 0))
        gameGrid[x][y] = { 0 };
    else if ((y == 9) && (colorNum == gameGrid[x][y - 1] || colorNum == gameGrid[x + 1][y]))
    {
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
                gameGrid[i][j] = { 0 };
    }
    else if (gameGrid[x][y - 1] == 0 && gameGrid[x + 1][y] == 0 && gameGrid[x][y + 1] == 0)
        gameGrid[x][y] = { 0 };
    else if (colorNum == gameGrid[x][y - 1] || colorNum == gameGrid[x + 1][y] || colorNum == gameGrid[x][y + 1])
    {
        for (int i = 0; i < 20; i++)
            for (int j = 0; j < 10; j++)
                gameGrid[i][j] = { 0 };
    }
    else
    {
        if (y < 5)
        {
            gameGrid[x][y] = 0;
            gameGrid[x + 1][y] = 0;
            gameGrid[x + 1][y + 1] = 0;
            gameGrid[x + 1][y + 2] = 0;
            gameGrid[x + 1][y + 3] = 0;
        }
        else if (y > 4)
        {
            gameGrid[x][y] = 0;
            gameGrid[x + 1][y] = 0;
            gameGrid[x + 1][y - 1] = 0;
            gameGrid[x + 1][y - 2] = 0;
            gameGrid[x + 1][y - 3] = 0;
        }
    }
}

void movement(int& delta_x)
{
    for (int i = 0; i < 4; i++)
    {
        point_1[i][0] += delta_x;
    }
    for (int i = 0; i < 4; i++)
    {
        if (!anamoly())
        {
            for (i = 0; i < 4; i++)
            {
                point_1[i][0] -= delta_x;
            }
            break;
        }
    }
    delta_x = 0;
}
void rot(bool& rotate)
{
    if (rotate)
    {

        bool anm = 0;
        for (int i = 0; i < 4; i++)
        {
            point[i][0] = point_1[i][0];
            point[i][1] = point_1[i][1];
            // std::cout<<"x: "<<point[i][0]<<" y: "<<point[i][1]<<"\n";
        }
        std::cout << "\n";
        int x, y;
        int px = point[1][0];
        int py = point[1][1];
        // std::cout<<"px: "<<px<<" py: "<<py<<" \n\n";

        for (int i = 0; i < 4; i++)
        {

            x = point[i][1] - py;
            y = point[i][0] - px;
            point[i][0] = px - x;
            point[i][1] = py + y;
            if (point[i][0] < 0)
            {
                anm = 1;
            }
        }
        // cout<<anm<<endl;
        if (anm == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                point_1[i][0] = point[i][0];
                point_1[i][1] = point[i][1];
                // std::cout<<"rx: "<<point_1[i][0]<<" ry: "<<point_1[i][1]<<"\n";
            }
            // std::cout<<"\n";
        }
        else
        {
        }
    }
    rotate = 0;
}
void lineremove(int& score, int& level)
{
    int line = 0, no_of_lines = 0;
    for (int i = 0; i < 20; i++)
    {
        line = 0;
        for (int j = 0; j < 10; j++)
        {
            // cout<<gameGrid[i][j]<<" ";
            if (gameGrid[i][j] == 0)
            {
                line++;
            }
        }
        //  cout<<endl<<"line"<<line<<endl;
        if (line == 0)
        {
            no_of_lines++;
            for (int j = 0; j < 10; j++)
                gameGrid[i][j] = { 0 };
            int l;
            int temp;
            for (l = i; l > 0; l--)
            {
                for (int j = 0; j < 10; j++)
                {
                    temp = gameGrid[l][j];
                    gameGrid[l][j] = gameGrid[l - 1][j];
                    gameGrid[l - 1][j] = temp;
                }
            }
        }
    }
    if (no_of_lines == 1)
        score = score + (10 * level);
    else if (no_of_lines == 2)
        score = score + (30 * level);
    else if (no_of_lines == 3)
        score = score + (60 * level);
    else if (no_of_lines == 4)
        score = score + (100 * level);
    if (no_of_lines != 0)
        std::cout << "Score = " << score << "\n";
}
void shadow(int gridShadow[][10], int blockShadow[][4], float& timer, float& delay, int& delta_x, int& n, int space, int& level, bool& rotate)
{
    void rot_shadow(bool& rotate);
    void movement_shadow(int& delta_x);
    movement_shadow(delta_x);
    rot_shadow(rotate);
    if (timer > delay)
    {
        int max = p1[0][1], distance_y;
        for (int i = 1; i < 4; i++)
        {
            if (p1[i][1] > max)
                max = p1[i][1];
        }
        distance_y = 19 - max;
        for (int i = 0; i < 4; i++)
        {
            p1[i][1] += distance_y;
            while (!anamoly())
            {
                for (int i = 0; i < 4; i++)
                    p1[i][1] -= 1;
            }
        }
        for (int i = 0; i < 4; i++)
        {
            p2[i][0] = p1[i][0];
            p2[i][1] = p1[i][1];
        }
        int i = 0;

        // if (n == 7)
        //     bomb(i, colorNum);
        if (level != 2)
            delay = 0.3;
        if (n != 7)
        {
            for (int i = 0; i < 4; i++)
            {
                gridShadow[p2[i][1]][p2[i][0]] = 8;
                // std::cout<<"y "<<point_2[i][1]<<"\nx "<<point_2[i][0]<<"\n";
                //  cout << "gg: " << gameGrid[point_2[i][1]][point_2[i][0]] << endl;
            }
        }
        // n = rand() % 8;
        //  delta_x = rand() % 10;
        if (n == 7)
            delay = 0.04;

        for (int i = 0; i < 4; i++)
        {
            p1[i][0] = blockShadow[n][i] % 2;
            p1[i][1] = blockShadow[n][i] / 2;
            //                std::cout<<"x: "<<point_1[i][0]<<"\n";
            //                std::cout<<"y: "<<point_1[i][1]<<"\n";
        }

        // std::cout<<"End\n";

        timer = 0;
    }
}
void movement_shadow(int& delta_x)
{
    for (int i = 0; i < 4; i++)
    {
        p1[i][0] += delta_x;
    }
    for (int i = 0; i < 4; i++)
    {
        if (!anamoly())
        {
            for (i = 0; i < 4; i++)
            {
                p1[i][0] -= delta_x;
            }
            break;
        }
    }
    delta_x = 0;
}
void rot_shadow(bool& rotate)
{
    if (rotate)
    {

        bool anm = 0;
        for (int i = 0; i < 4; i++)
        {
            point[i][0] = p1[i][0];
            point[i][1] = p1[i][1];
            // std::cout<<"x: "<<point[i][0]<<" y: "<<point[i][1]<<"\n";
        }
        std::cout << "\n";
        int x, y;
        int px = point[1][0];
        int py = point[1][1];
        // std::cout<<"px: "<<px<<" py: "<<py<<" \n\n";

        for (int i = 0; i < 4; i++)
        {

            x = point[i][1] - py;
            y = point[i][0] - px;
            point[i][0] = px - x;
            point[i][1] = py + y;
            if (point[i][0] < 0)
            {
                anm = 1;
            }
        }
        // cout<<anm<<endl;
        if (anm == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                p1[i][0] = point[i][0];
                p1[i][1] = point[i][1];
                // std::cout<<"rx: "<<point_1[i][0]<<" ry: "<<point_1[i][1]<<"\n";
            }
            // std::cout<<"\n";
        }
        else
        {
        }
    }
    rotate = 0;
}
/*** YOUR FUNCTIONS END HERE ***/ //
///////////////////////////////////
