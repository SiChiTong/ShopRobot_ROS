#include <queue>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include <global_path_planning_node.h>

#define num_x 10
#define num_y 10

namespace shop{
namespace pathplan{

using namespace std;
typedef pair<int, int> Coord;

class GlobalPlan : public GlobalBase
{
public:
    GlobalPlan(std::string name): GlobalBase(name), INF(999)
    {
        flag = 1;
        plan_flag_1 = 0;
        plan_flag_2 = 0;
        plan_flag_3 = 0;
        plan_flag_4 = 0;

        for(int i=0; i<4; i++)
            robot_level.push_back(i+1);

        int map[num_x][num_y] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        PositionOfObstacles(map);

        memcpy(map_1, map, sizeof(map));
        memcpy(map_2, map, sizeof(map));
        memcpy(map_3, map, sizeof(map));
        memcpy(map_4, map, sizeof(map));

    }

    void RobotGlobalPlanning()
    {
        if(flag == 1)
        {
            auto now_1 = GetNowCoord(1);
            auto end_1 = GetTargetCoord(1);

            auto now_2 = GetNowCoord(2);
            auto end_2 = GetTargetCoord(2);

            auto now_3 = GetNowCoord(3);
            auto end_3 = GetTargetCoord(3);

            auto now_4 = GetNowCoord(4);
            auto end_4 = GetTargetCoord(4);

            queue<Coord> path_1 = PathPlanning(Coord(now_1.x, now_1.y), Coord(end_1.x, end_1.y));
            queue<Coord> path_2 = PathPlanning(Coord(now_2.x, now_2.y), Coord(end_2.x, end_2.y));
            queue<Coord> path_3 = PathPlanning(Coord(now_3.x, now_3.y), Coord(end_3.x, end_3.y));
            queue<Coord> path_4 = PathPlanning(Coord(now_4.x, now_4.y), Coord(end_4.x, end_4.y));
            queue<Coord> temp_path_1 = path_1, temp_path_2 = path_2, temp_path_3 = path_3, temp_path_4 = path_4;
        
            while(temp_path_1.size())
            {
                Coord local_1 = temp_path_1.front();
                temp_path_1.pop();

                map_1[local_1.first][local_1.second] = 1;
            }
            memcpy(map_2, map_1, sizeof(map_1));



            while(temp_path_2.size())
            {
                Coord local_2 = temp_path_2.front();
                temp_path_2.pop();

                map_2[local_2.first][local_2.second] += 1;
        
            }
            memcpy(map_3, map_2, sizeof(map_2));


            while(temp_path_3.size())
            {
                Coord local_3 = temp_path_3.front();
                temp_path_3.pop();

                map_3[local_3.first][local_3.second] += 1;
                
            }
            memcpy(map_4, map_3, sizeof(map_3));

            
            while(temp_path_4.size())
            {
                Coord local_4 = temp_path_4.front();
                temp_path_4.pop();

                map_4[local_4.fi rst][local_4.second] += 1;
                    
            }
            flag += 1;
        }
        else
        {

            for(int i=0; i<4; i++) //计算优先级为2的机器人所停位置
            {
                if(robot_level[i] == 2)
                {
                    vehicle_num = i+1;
                    if(vehicle_num == 1)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_1.size() == 0)
                            {
                                final_coord_1 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_1.front();
                            path_1.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_1 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                            
                        }
                    }

                    if(vehicle_num == 2)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_2.size() == 0)
                            {
                                final_coord_2 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_2.front();
                            path_2.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_2 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }

                    if(vehicle_num == 3)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_3.size() == 0)
                            {
                                final_coord_3 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_3.front();
                            path_3.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_3 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }

                    if(vehicle_num == 4)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_4.size() == 0)
                            {
                                final_coord_1 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_4.front();
                            path_4.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_2[stop_coord.first][stop_coord.second] -= 1;
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_4 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }
                }
            }

            for(int i=0; i<4; i++) //计算优先级为3的机器人所停位置
            {
                if(robot_level[i] == 3)
                {
                    vehicle_num = i+1;
                    if(vehicle_num == 1)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_1.size() == 0)
                            {
                                final_coord_1 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_1.front();
                            path_1.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_1 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                            
                        }
                    }

                    if(vehicle_num == 2)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_2.size() == 0)
                            {
                                final_coord_2 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_2.front();
                            path_2.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_2 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }

                    if(vehicle_num == 3)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_3.size() == 0)
                            {
                                final_coord_3 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_3.front();
                            path_3.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_3 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }

                    if(vehicle_num == 4)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_4.size() == 0)
                            {
                                final_coord_1 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_4.front();
                            path_4.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_3[stop_coord.first][stop_coord.second] -= 1;
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_4 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }
                }
            }

            for(int i=0; i<4; i++) //计算优先级为4的机器人所停位置
            {
                if(robot_level[i] == 4)
                {
                    vehicle_num = i+1;
                    if(vehicle_num == 1)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_1.size() == 0)
                            {
                                final_coord_1 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_1.front();
                            path_1.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_1 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                            
                        }
                    }

                    if(vehicle_num == 2)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_2.size() == 0)
                            {
                                final_coord_2 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_2.front();
                            path_2.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_2 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }

                    if(vehicle_num == 3)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_3.size() == 0)
                            {
                                final_coord_3 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_3.front();
                            path_3.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_3 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }

                    if(vehicle_num == 4)
                    {
                        int arrive_flag = 1
                        while(arrive_flag)
                        {
                            if(path_4.size() == 0)
                            {
                                final_coord_1 = last_coord;
                                break;
                            }

                            Coord last_coord;
                            Coord stop_coord = path_4.front();
                            path_4.pop();

                            if(map_2[stop_coord.first][stop_coord.second] == 1)
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                            }
                            else
                            {
                                map_4[stop_coord.first][stop_coord.second] -= 1;
                                final_coord_4 = last_coord;
                                arrive_flag = 0;
                            }
                            last_coord = stop_coord;
                        }
                    }
                }
            }

            for(int i=0; i<4; i++) //计算优先级为1的机器人已走过的路径
            {
                if(robot_level[i] == 1)
                {
                    if(i+1 == 1)
                    {
                        auto now_1 = GetNowCoord(1);
                        int no_arrive = 1;

                        while(no_arrive)
                        {
                            if(path_1.size() == 0)
                            {
                                break;
                            }

                            Coord arrive_coord = path_1.front();

                            if(arrive_coord.first != now_1.x || arrive_coord.second != now_1.y)
                            {
                                path_1.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                            }
                            else
                            {
                                path_1.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                                no_arrive = 0;
                            }

                        }
                    }

                    if(i+1 == 2)
                    {
                        auto now_2 = GetNowCoord(2);
                        int no_arrive = 1;
                        
                        while(no_arrive)
                        {
                            if(path_2.size() == 0)
                            {
                                break;
                            }

                            Coord arrive_coord = path_2.front();

                            if(arrive_coord.first != now_2.x || arrive_coord.second != now_2.y)
                            {
                                path_2.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                            }
                            else
                            {
                                path_2.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                                no_arrive = 0;
                            }

                        }
                    }

                    if(i+1 == 3)
                    {
                        auto now_3 = GetNowCoord(3);
                        int no_arrive = 1;
                        
                        while(no_arrive)
                        {
                            if(path_3.size() == 0)
                            {
                                break;
                            }

                            Coord arrive_coord = path_3.front();

                            if(arrive_coord.first != now_3.x || arrive_coord.second != now_3.y)
                            {
                                path_3.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                            }
                            else
                            {
                                path_3.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                                no_arrive = 0;
                            }

                        }
                    }

                    if(i+1 == 4)
                    {
                        auto now_4 = GetNowCoord(4);
                        int no_arrive = 1;
                        
                        while(no_arrive)
                        {
                            if(path_4.size() == 0)
                            {
                                break;
                            }

                            Coord arrive_coord = path_4.front();

                            if(arrive_coord.first != now_4.x || arrive_coord.second != now_4.y)
                            {
                                path_4.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                            }
                            else
                            {
                                path_4.pop();
                                map_1[arrive_coord.first][arrive_coord.second] -= 1;
                                no_arrive = 0;
                            }

                        }
                    }
                }
            }
            
            auto now_1 = GetNowCoord(1);
            auto end_1 = GetTargetCoord(1);

            if(now_1.x == end_1.x && now_1.y == end_1.y && plan_flag_1 == 0)
                plan_flag_1 = 1;

            auto now_2 = GetNowCoord(2);
            auto end_2 = GetTargetCoord(2);

            if(now_2.x == end_2.x && now_2.y == end_2.y && plan_flag_2 == 0)
                plan_flag_2 = 1;

            auto now_3 = GetNowCoord(3);
            auto end_3 = GetTargetCoord(3);

            if(now_3.x == end_3.x && now_3.y == end_3.y && plan_flag_3 == 0)
                plan_flag_3 = 1;

            auto now_4 = GetNowCoord(4);
            auto end_4 = GetTargetCoord(4);

            if(now_4.x == end_4.x && now_4.y == end_4.y && plan_flag_4 == 0)
                plan_flag_4 = 1;

            if(plan_flag_1 == 1)  //给编号为1的机器人重新规划路径
            {
                if(robot_level[0] == 1)
                {
                    memcpy(map_1, map_2, sizeof(map_2));
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 2]
                            robot_level[i] = 1;
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_1 = GetNowCoord(1);
                    auto end_1 = GetTargetCoord(1);

                    path_1 = PathPlanning(Coord(now_1.x, now_1.y), Coord(end_1.x, end_1.y));
                    temp_path_1 = path_1;

                    while(temp_path_1.size())
                    {
                        Coord local_1 = temp_path_1.front();
                        temp_path_1.pop();

                        map_4[local_1.fi rst][local_1.second] += 1;
                    }

                }

                if(robot_level[0] == 2)
                {
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_1 = GetNowCoord(1);
                    auto end_1 = GetTargetCoord(1);

                    path_1 = PathPlanning(Coord(now_1.x, now_1.y), Coord(end_1.x, end_1.y));
                    temp_path_1 = path_1;

                    while(temp_path_1.size())
                    {
                        Coord local_1 = temp_path_1.front();
                        temp_path_1.pop();

                        map_4[local_1.fi rst][local_1.second] += 1;
                    }

                }

                if(robot_level[0] == 3)
                {

                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_1 = GetNowCoord(1);
                    auto end_1 = GetTargetCoord(1);

                    path_1 = PathPlanning(Coord(now_1.x, now_1.y), Coord(end_1.x, end_1.y));
                    temp_path_1 = path_1;

                    while(temp_path_1.size())
                    {
                        Coord local_1 = temp_path_1.front();
                        temp_path_1.pop();

                        map_4[local_1.fi rst][local_1.second] += 1;
                    }

                }

                if(robot_level[0] == 4)
                {

                    
                    auto now_1 = GetNowCoord(1);
                    auto end_1 = GetTargetCoord(1);

                    path_1 = PathPlanning(Coord(now_1.x, now_1.y), Coord(end_1.x, end_1.y));
                    temp_path_1 = path_1;

                    while(temp_path_1.size())
                    {
                        Coord local_1 = temp_path_1.front();
                        temp_path_1.pop();

                        map_4[local_1.fi rst][local_1.second] += 1;
                    }

                }

                plan_flag_1 = 0;
            }

            if(plan_flag_2 == 1)  //给编号为2的机器人重新规划路径
            {
                if(robot_level[1] == 1)
                {
                    memcpy(map_1, map_2, sizeof(map_2));
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 2]
                            robot_level[i] = 1;
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_2 = GetNowCoord(2);
                    auto end_2 = GetTargetCoord(2);

                    path_2 = PathPlanning(Coord(now_2.x, now_2.y), Coord(end_2.x, end_2.y));
                    temp_path_2 = path_2;

                    while(temp_path_2.size())
                    {
                        Coord local_2 = temp_path_2.front();
                        temp_path_2.pop();

                        map_4[local_2.fi rst][local_2.second] += 1;
                    }

                }

                if(robot_level[0] == 2)
                {
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_2 = GetNowCoord(2);
                    auto end_2 = GetTargetCoord(2);

                    path_2 = PathPlanning(Coord(now_2.x, now_2.y), Coord(end_2.x, end_2.y));
                    temp_path_2 = path_2;

                    while(temp_path_2.size())
                    {
                        Coord local_2 = temp_path_2.front();
                        temp_path_2.pop();

                        map_4[local_2.fi rst][local_2.second] += 1;
                    }
                }

                if(robot_level[0] == 3)
                {

                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_2 = GetNowCoord(2);
                    auto end_2 = GetTargetCoord(2);

                    path_2 = PathPlanning(Coord(now_2.x, now_2.y), Coord(end_2.x, end_2.y));
                    temp_path_2 = path_2;

                    while(temp_path_2.size())
                    {
                        Coord local_2 = temp_path_2.front();
                        temp_path_2.pop();

                        map_4[local_2.fi rst][local_2.second] += 1;
                    }

                }

                if(robot_level[0] == 4)
                {

                    
                    auto now_2 = GetNowCoord(2);
                    auto end_2 = GetTargetCoord(2);

                    path_2 = PathPlanning(Coord(now_2.x, now_2.y), Coord(end_2.x, end_2.y));
                    temp_path_2 = path_2;

                    while(temp_path_2.size())
                    {
                        Coord local_2 = temp_path_2.front();
                        temp_path_2.pop();

                        map_4[local_2.fi rst][local_2.second] += 1;
                    }

                }

                plan_flag_2 = 0;
            }

            if(plan_flag_3 == 1)  //给编号为3的机器人重新规划路径
            {
                if(robot_level[2] == 1)
                {
                    memcpy(map_1, map_2, sizeof(map_2));
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 2]
                            robot_level[i] = 1;
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_3 = GetNowCoord(3);
                    auto end_3 = GetTargetCoord(3);

                    path_3 = PathPlanning(Coord(now_3.x, now_3.y), Coord(end_3.x, end_3.y));
                    temp_path_3 = path_3;

                    while(temp_path_3.size())
                    {
                        Coord local_3 = temp_path_3.front();
                        temp_path_3.pop();

                        map_4[local_3.fi rst][local_3.second] += 1;
                    }

                }

                if(robot_level[0] == 2)
                {
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_3 = GetNowCoord(3);
                    auto end_3 = GetTargetCoord(3);

                    path_3 = PathPlanning(Coord(now_3.x, now_3.y), Coord(end_3.x, end_3.y));
                    temp_path_3 = path_3;

                    while(temp_path_3.size())
                    {
                        Coord local_3 = temp_path_3.front();
                        temp_path_3.pop();

                        map_4[local_3.fi rst][local_3.second] += 1;
                    }

                }

                if(robot_level[0] == 3)
                {

                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_3 = GetNowCoord(3);
                    auto end_3 = GetTargetCoord(3);

                    path_3 = PathPlanning(Coord(now_3.x, now_3.y), Coord(end_3.x, end_3.y));
                    temp_path_3 = path_3;

                    while(temp_path_3.size())
                    {
                        Coord local_3 = temp_path_3.front();
                        temp_path_3.pop();

                        map_4[local_3.fi rst][local_3.second] += 1;
                    }


                }

                if(robot_level[0] == 4)
                {

                    
                    auto now_3 = GetNowCoord(3);
                    auto end_3 = GetTargetCoord(3);

                    path_3 = PathPlanning(Coord(now_3.x, now_3.y), Coord(end_3.x, end_3.y));
                    temp_path_3 = path_3;

                    while(temp_path_3.size())
                    {
                        Coord local_3 = temp_path_3.front();
                        temp_path_3.pop();

                        map_4[local_3.fi rst][local_3.second] += 1;
                    }


                }

                plan_flag_3 = 0;
            }

            if(plan_flag_4 == 1)  //给编号为4的机器人重新规划路径
            {
                if(robot_level[2] == 1)
                {
                    memcpy(map_1, map_2, sizeof(map_2));
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 2]
                            robot_level[i] = 1;
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_4 = GetNowCoord(4);
                    auto end_4 = GetTargetCoord(4);

                    path_4 = PathPlanning(Coord(now_4.x, now_4.y), Coord(end_4.x, end_4.y));
                    temp_path_4 = path_4;

                    while(temp_path_4.size())
                    {
                        Coord local_4 = temp_path_4.front();
                        temp_path_4.pop();

                        map_4[local_4.first][local_4.second] += 1;
                    }

                }

                if(robot_level[0] == 2)
                {
                    memcpy(map_2, map_3, sizeof(map_3));
                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 3]
                            robot_level[i] = 2;
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_4 = GetNowCoord(4);
                    auto end_4 = GetTargetCoord(4);

                    path_4 = PathPlanning(Coord(now_4.x, now_4.y), Coord(end_4.x, end_4.y));
                    temp_path_4 = path_4;

                    while(temp_path_4.size())
                    {
                        Coord local_4 = temp_path_4.front();
                        temp_path_4.pop();

                        map_4[local_4.first][local_4.second] += 1;
                    }

                }

                if(robot_level[0] == 3)
                {

                    memcpy(map_3, map_4, sizeof(map_4));

                    for(int i=0; i<4; i++)
                    {
                        if[robot_level[i] == 4]
                            robot_level[i] = 3;
                    }
                    robot_level[0] = 4;

                    auto now_4 = GetNowCoord(4);
                    auto end_4 = GetTargetCoord(4);

                    path_4 = PathPlanning(Coord(now_4.x, now_4.y), Coord(end_4.x, end_4.y));
                    temp_path_4 = path_4;

                    while(temp_path_4.size())
                    {
                        Coord local_4 = temp_path_4.front();
                        temp_path_4.pop();

                        map_4[local_4.first][local_4.second] += 1;
                    }


                }

                if(robot_level[0] == 4)
                {

                    
                   auto now_4 = GetNowCoord(4);
                    auto end_4 = GetTargetCoord(4);

                    path_4 = PathPlanning(Coord(now_4.x, now_4.y), Coord(end_4.x, end_4.y));
                    temp_path_4 = path_4;

                    while(temp_path_4.size())
                    {
                        Coord local_4 = temp_path_4.front();
                        temp_path_4.pop();

                        map_4[local_4.first][local_4.second] += 1;
                    }


                }

                plan_flag_4 = 0;
            }
        }     
    }

    void PositionOfObstacles(int map[num_x][num_y])
    {
        auto location = GetRoadblock();
        switch (location)
        {
            case 1:
                map[8][1] = 1;
                break;
            case 2:
                map[8][4] = 1;
                break;
            case 3:
                map[8][8] = 11;
                break;
            case 4:
                map[5][7] = 1;
                break;
            case 5:
                map[1][8] = 1;
                break;
            case 6:
                map[1][5] = 1;
                break;
            default:
                break;
        }
    }

    queue<Coord> RecordShortestPath(int x, int y, Coord begin, Coord map_path[num_x][num_y])
    {
        queue que;

        if(x == begin.first && y ==begin.second)
        {
            que.push(begin);
            return que;
        }

        Coord local = map_path[x][y];
        que = RecordShortestPath(local.first, local.second, begin, map_path);
        que.push(local);
        return que
    }

    queue<Coord> PathPlanning(Coord begin, Coord end)
    {
        queue<Coord> que, path;
        Coord map_path[num_x][num_y];

        int move_x = {0, 0, 1, -1}, move_y = {1, -1, 0, 0};

        int map[num_x][num_y] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                 {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        PositionOfObstacles(map);
        auto now_1 = GetNowCoord(1);
        auto now_2 = GetNowCoord(2);
        auto now_3 = GetNowCoord(3);
        auto now_4 = GetNowCoord(4);

        map9[now_1.x][now_1.y] = 1;
        map9[now_2.x][now_2.y] = 1;
        map9[now_3.x][now_3.y] = 1;
        map9[now_4.x][now_4.y] = 1;


        que.push(begin);
        map[begin.first][begin.second] = 1;
        map_path[begin.first][begin.second] = Coord(-1, -1);

        while(que.size())
        {
            Coord local = que.front();
            que.pop();

            int i = 0;
            for(int i = 0; i<4; i++)
            {
                int temp_x = local.first + move_x[i];
                int temp_y = local.second + move_y[i];

                if(0 <= temp_x && temp_x < num_x && 0 <= temp_y && temp_y < num_y && map[temp_x][temp_y] != 1)
                {
                    que.push(Coord(temp_x, temp_y));
                    map_path[temp_x][temp_y] = local;
                    map[temp_x][temp_y] = 1;
                    if(temp_x == end.first && temp_y == end.second)
                        break;
                }
            }
            if(i != 4)
                break;
        }

        path = RecordShortestPath(path, end.first, end.second, begin, map_path);
        return path;
    }

private:
    const int INF;

    int flag, plan_flag_1, plan_flag_2, plan_flag_3, plan_flag_4;

    int map_1[num_x][num_y];
    int map_2[num_x][num_y];
    int map_3[num_x][num_y];
    int map_4[num_x][num_y];

    vector<int> robot_level;

    Coord final_coord_1, final_coord_2, final_coord_3, final_coord_4;

}





} // namespace pathplan
} // namespace shop
