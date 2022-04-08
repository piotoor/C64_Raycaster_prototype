#include <SFML/Graphics.hpp>
#include "GameMap.h"

#include <iostream>
#include <vector>
#include <cmath>

//using namespace std;
//
//
constexpr int screenWidth = 40;
constexpr int screenHeight = 24;
//constexpr uint16_t drawDistance = 256;


//vector<vector<uint16_t>> sinTable = {
//    {
//        65535, 2607, 1304, 869, 652, 522, 436, 374, 328, 292, 263, 239, 220, 204, 189, 177, 167, 157, 149, 142, 135, 129, 124, 119, 115, 111, 107, 104, 100, 97, 95, 92, 90, 88, 86, 84, 82, 81, 79, 78, 76, 75, 74, 73, 72, 71, 70, 70, 69, 68, 67, 67, 66, 66, 65, 65, 65, 64, 64, 64, 64, 64, 64, 64, 64,
//    },
//    {
//        65535, 5215, 2608, 1739, 1305, 1045, 872, 748, 656, 584, 526, 479, 440, 408, 379, 355, 334, 315, 299, 284, 271, 259, 248, 239, 230, 222, 214, 208, 201, 195, 190, 185, 181, 176, 172, 169, 165, 162, 159, 156, 153, 151, 149, 147, 145, 143, 141, 140, 138, 137, 135, 134, 133, 132, 131, 131, 130, 129, 129, 128, 128, 128, 128, 128, 128,
//    },
//    {
//        65535, 7823, 3912, 2609, 1958, 1568, 1308, 1123, 984, 876, 790, 719, 661, 612, 569, 533, 501, 473, 449, 427, 407, 389, 373, 358, 345, 333, 322, 312, 302, 293, 285, 278, 271, 265, 259, 253, 248, 243, 239, 234, 230, 227, 223, 220, 217, 214, 212, 210, 207, 205, 203, 202, 200, 199, 197, 196, 195, 194, 194, 193, 192, 192, 192, 192, 192,
//    },
//    {
//        65535, 10431, 5217, 3479, 2611, 2091, 1744, 1497, 1312, 1168, 1053, 959, 881, 816, 759, 711, 668, 631, 598, 569, 543, 519, 497, 478, 460, 444, 429, 416, 403, 391, 381, 371, 362, 353, 345, 338, 331, 324, 318, 313, 307, 303, 298, 294, 290, 286, 283, 280, 277, 274, 271, 269, 267, 265, 263, 262, 261, 259, 258, 257, 257, 256, 256, 256, 256,
//    },
//    {
//        65535, 13039, 6521, 4349, 3264, 2614, 2180, 1871, 1640, 1460, 1316, 1199, 1102, 1020, 949, 889, 836, 789, 748, 711, 678, 649, 622, 598, 575, 555, 537, 520, 504, 489, 476, 464, 452, 441, 431, 422, 413, 405, 398, 391, 384, 378, 373, 367, 362, 358, 353, 350, 346, 342, 339, 337, 334, 332, 329, 327, 326, 324, 323, 322, 321, 320, 320, 320, 320,
//    },
//    {
//        65535, 15647, 7825, 5219, 3917, 3136, 2617, 2246, 1968, 1752, 1580, 1439, 1322, 1224, 1139, 1066, 1003, 947, 898, 854, 814, 779, 746, 717, 691, 666, 644, 624, 605, 587, 571, 556, 543, 530, 518, 507, 496, 487, 478, 469, 461, 454, 447, 441, 435, 429, 424, 420, 415, 411, 407, 404, 401, 398, 395, 393, 391, 389, 388, 386, 385, 385, 384, 384, 384,
//    },
//    {
//        65535, 18254, 9130, 6089, 4570, 3659, 3053, 2620, 2296, 2044, 1843, 1679, 1543, 1428, 1329, 1244, 1170, 1105, 1047, 996, 950, 908, 871, 837, 806, 778, 752, 728, 706, 685, 667, 649, 633, 618, 604, 591, 579, 568, 557, 547, 538, 530, 522, 514, 507, 501, 495, 490, 484, 480, 475, 471, 468, 464, 461, 459, 456, 454, 452, 451, 450, 449, 448, 448, 448,
//    },
//    {
//        65535, 20862, 10434, 6959, 5223, 4182, 3489, 2994, 2624, 2336, 2107, 1919, 1763, 1632, 1519, 1422, 1337, 1263, 1197, 1138, 1086, 1038, 995, 957, 921, 889, 859, 832, 807, 783, 762, 742, 724, 706, 691, 676, 662, 649, 637, 626, 615, 606, 596, 588, 580, 573, 566, 560, 554, 548, 543, 539, 535, 531, 527, 524, 522, 519, 517, 515, 514, 513, 512, 512, 512,
//    },
//    {
//        65535, 23470, 11738, 7829, 5876, 4705, 3925, 3369, 2952, 2628, 2370, 2159, 1984, 1836, 1709, 1600, 1505, 1421, 1347, 1281, 1221, 1168, 1120, 1076, 1036, 1000, 966, 936, 907, 881, 857, 835, 814, 795, 777, 760, 745, 730, 717, 704, 692, 681, 671, 662, 653, 644, 637, 630, 623, 617, 611, 606, 601, 597, 593, 590, 587, 584, 582, 580, 578, 577, 576, 576, 576,
//    },
//    {
//        65535, 26078, 13043, 8699, 6529, 5228, 4361, 3743, 3280, 2921, 2633, 2399, 2204, 2040, 1899, 1778, 1672, 1579, 1496, 1423, 1357, 1298, 1244, 1196, 1151, 1111, 1074, 1040, 1008, 979, 953, 928, 905, 883, 863, 845, 827, 811, 796, 782, 769, 757, 746, 735, 725, 716, 707, 700, 692, 685, 679, 674, 668, 664, 659, 655, 652, 649, 647, 644, 643, 641, 640, 640, 640,
//    },
//    {
//        65535, 28686, 14347, 9569, 7182, 5751, 4797, 4117, 3608, 3213, 2897, 2639, 2425, 2244, 2089, 1956, 1839, 1737, 1646, 1565, 1493, 1428, 1369, 1315, 1267, 1222, 1181, 1144, 1109, 1077, 1048, 1020, 995, 972, 950, 929, 910, 893, 876, 861, 846, 833, 820, 809, 798, 788, 778, 770, 762, 754, 747, 741, 735, 730, 725, 721, 717, 714, 711, 709, 707, 705, 704, 704, 704,
//    },
//    {
//        65535, 31294, 15651, 10439, 7835, 6273, 5234, 4492, 3936, 3505, 3160, 2879, 2645, 2448, 2279, 2133, 2006, 1895, 1796, 1708, 1629, 1558, 1493, 1435, 1382, 1333, 1289, 1248, 1210, 1175, 1143, 1113, 1086, 1060, 1036, 1014, 993, 974, 956, 939, 923, 909, 895, 882, 870, 859, 849, 840, 831, 823, 815, 808, 802, 796, 791, 787, 783, 779, 776, 773, 771, 770, 768, 768, 768,
//    },
//    {
//        65535, 33902, 16956, 11309, 8488, 6796, 5670, 4866, 4264, 3797, 3424, 3119, 2866, 2652, 2469, 2311, 2174, 2053, 1945, 1850, 1764, 1687, 1618, 1555, 1497, 1444, 1396, 1352, 1311, 1273, 1238, 1206, 1176, 1148, 1122, 1098, 1076, 1055, 1035, 1017, 1000, 984, 970, 956, 943, 931, 920, 910, 900, 891, 883, 876, 869, 863, 857, 852, 848, 844, 841, 838, 836, 834, 833, 832, 832,
//    },
//    {
//        65535, 36509, 18260, 12179, 9141, 7319, 6106, 5240, 4592, 4089, 3687, 3359, 3086, 2856, 2659, 2489, 2341, 2211, 2095, 1992, 1900, 1817, 1742, 1674, 1612, 1556, 1504, 1456, 1412, 1371, 1334, 1299, 1267, 1237, 1209, 1183, 1159, 1136, 1115, 1095, 1077, 1060, 1044, 1029, 1015, 1003, 991, 980, 969, 960, 951, 943, 936, 929, 923, 918, 913, 909, 905, 902, 900, 898, 897, 896, 896,
//    },
//    {
//        65535, 39117, 19564, 13049, 9794, 7842, 6542, 5615, 4920, 4381, 3950, 3599, 3307, 3060, 2849, 2667, 2508, 2368, 2245, 2135, 2036, 1947, 1867, 1794, 1727, 1667, 1611, 1560, 1513, 1469, 1429, 1392, 1357, 1325, 1295, 1267, 1241, 1217, 1195, 1174, 1154, 1136, 1119, 1103, 1088, 1074, 1061, 1050, 1039, 1028, 1019, 1011, 1003, 996, 989, 983, 978, 974, 970, 967, 964, 962, 961, 960, 960,
//    },
//    {
//        65535, 41725, 20869, 13919, 10447, 8365, 6978, 5989, 5248, 4673, 4214, 3839, 3527, 3264, 3039, 2845, 2675, 2526, 2395, 2277, 2172, 2077, 1991, 1914, 1843, 1778, 1718, 1664, 1614, 1567, 1524, 1485, 1448, 1413, 1382, 1352, 1324, 1298, 1274, 1252, 1231, 1212, 1193, 1176, 1161, 1146, 1132, 1120, 1108, 1097, 1087, 1078, 1070, 1062, 1055, 1049, 1044, 1039, 1035, 1031, 1028, 1026, 1025, 1024, 1024,
//    },
//};
//
//vector<vector<uint16_t>> cosTable = {
//    {
//        64, 64, 64, 64, 64, 64, 64, 64, 65, 65, 65, 66, 66, 67, 67, 68, 69, 70, 70, 71, 72, 73, 74, 75, 76, 78, 79, 81, 82, 84, 86, 88, 90, 92, 95, 97, 100, 104, 107, 111, 115, 119, 124, 129, 135, 142, 149, 157, 167, 177, 189, 204, 220, 239, 263, 292, 328, 374, 436, 522, 652, 869, 1304, 2607, 65535,
//    },
//    {
//        128, 128, 128, 128, 128, 128, 129, 129, 130, 131, 131, 132, 133, 134, 135, 137, 138, 140, 141, 143, 145, 147, 149, 151, 153, 156, 159, 162, 165, 169, 172, 176, 181, 185, 190, 195, 201, 208, 214, 222, 230, 239, 248, 259, 271, 284, 299, 315, 334, 355, 379, 408, 440, 479, 526, 584, 656, 748, 872, 1045, 1305, 1739, 2608, 5215, 65535,
//    },
//    {
//        192, 192, 192, 192, 192, 193, 194, 194, 195, 196, 197, 199, 200, 202, 203, 205, 207, 210, 212, 214, 217, 220, 223, 227, 230, 234, 239, 243, 248, 253, 259, 265, 271, 278, 285, 293, 302, 312, 322, 333, 345, 358, 373, 389, 407, 427, 449, 473, 501, 533, 569, 612, 661, 719, 790, 876, 984, 1123, 1308, 1568, 1958, 2609, 3912, 7823, 65535,
//    },
//    {
//        256, 256, 256, 256, 257, 257, 258, 259, 261, 262, 263, 265, 267, 269, 271, 274, 277, 280, 283, 286, 290, 294, 298, 303, 307, 313, 318, 324, 331, 338, 345, 353, 362, 371, 381, 391, 403, 416, 429, 444, 460, 478, 497, 519, 543, 569, 598, 631, 668, 711, 759, 816, 881, 959, 1053, 1168, 1312, 1497, 1744, 2091, 2611, 3479, 5217, 10431, 65535,
//    },
//    {
//        320, 320, 320, 320, 321, 322, 323, 324, 326, 327, 329, 332, 334, 337, 339, 342, 346, 350, 353, 358, 362, 367, 373, 378, 384, 391, 398, 405, 413, 422, 431, 441, 452, 464, 476, 489, 504, 520, 537, 555, 575, 598, 622, 649, 678, 711, 748, 789, 836, 889, 949, 1020, 1102, 1199, 1316, 1460, 1640, 1871, 2180, 2614, 3264, 4349, 6521, 13039, 65535,
//    },
//    {
//        384, 384, 384, 385, 385, 386, 388, 389, 391, 393, 395, 398, 401, 404, 407, 411, 415, 420, 424, 429, 435, 441, 447, 454, 461, 469, 478, 487, 496, 507, 518, 530, 543, 556, 571, 587, 605, 624, 644, 666, 691, 717, 746, 779, 814, 854, 898, 947, 1003, 1066, 1139, 1224, 1322, 1439, 1580, 1752, 1968, 2246, 2617, 3136, 3917, 5219, 7825, 15647, 65535,
//    },
//    {
//        448, 448, 448, 449, 450, 451, 452, 454, 456, 459, 461, 464, 468, 471, 475, 480, 484, 490, 495, 501, 507, 514, 522, 530, 538, 547, 557, 568, 579, 591, 604, 618, 633, 649, 667, 685, 706, 728, 752, 778, 806, 837, 871, 908, 950, 996, 1047, 1105, 1170, 1244, 1329, 1428, 1543, 1679, 1843, 2044, 2296, 2620, 3053, 3659, 4570, 6089, 9130, 18254, 65535,
//    },
//    {
//        512, 512, 512, 513, 514, 515, 517, 519, 522, 524, 527, 531, 535, 539, 543, 548, 554, 560, 566, 573, 580, 588, 596, 606, 615, 626, 637, 649, 662, 676, 691, 706, 724, 742, 762, 783, 807, 832, 859, 889, 921, 957, 995, 1038, 1086, 1138, 1197, 1263, 1337, 1422, 1519, 1632, 1763, 1919, 2107, 2336, 2624, 2994, 3489, 4182, 5223, 6959, 10434, 20862, 65535,
//    },
//    {
//        576, 576, 576, 577, 578, 580, 582, 584, 587, 590, 593, 597, 601, 606, 611, 617, 623, 630, 637, 644, 653, 662, 671, 681, 692, 704, 717, 730, 745, 760, 777, 795, 814, 835, 857, 881, 907, 936, 966, 1000, 1036, 1076, 1120, 1168, 1221, 1281, 1347, 1421, 1505, 1600, 1709, 1836, 1984, 2159, 2370, 2628, 2952, 3369, 3925, 4705, 5876, 7829, 11738, 23470, 65535,
//    },
//    {
//        640, 640, 640, 641, 643, 644, 647, 649, 652, 655, 659, 664, 668, 674, 679, 685, 692, 700, 707, 716, 725, 735, 746, 757, 769, 782, 796, 811, 827, 845, 863, 883, 905, 928, 953, 979, 1008, 1040, 1074, 1111, 1151, 1196, 1244, 1298, 1357, 1423, 1496, 1579, 1672, 1778, 1899, 2040, 2204, 2399, 2633, 2921, 3280, 3743, 4361, 5228, 6529, 8699, 13043, 26078, 65535,
//    },
//    {
//        704, 704, 704, 705, 707, 709, 711, 714, 717, 721, 725, 730, 735, 741, 747, 754, 762, 770, 778, 788, 798, 809, 820, 833, 846, 861, 876, 893, 910, 929, 950, 972, 995, 1020, 1048, 1077, 1109, 1144, 1181, 1222, 1267, 1315, 1369, 1428, 1493, 1565, 1646, 1737, 1839, 1956, 2089, 2244, 2425, 2639, 2897, 3213, 3608, 4117, 4797, 5751, 7182, 9569, 14347, 28686, 65535,
//    },
//    {
//        768, 768, 768, 770, 771, 773, 776, 779, 783, 787, 791, 796, 802, 808, 815, 823, 831, 840, 849, 859, 870, 882, 895, 909, 923, 939, 956, 974, 993, 1014, 1036, 1060, 1086, 1113, 1143, 1175, 1210, 1248, 1289, 1333, 1382, 1435, 1493, 1558, 1629, 1708, 1796, 1895, 2006, 2133, 2279, 2448, 2645, 2879, 3160, 3505, 3936, 4492, 5234, 6273, 7835, 10439, 15651, 31294, 65535,
//    },
//    {
//        832, 832, 833, 834, 836, 838, 841, 844, 848, 852, 857, 863, 869, 876, 883, 891, 900, 910, 920, 931, 943, 956, 970, 984, 1000, 1017, 1035, 1055, 1076, 1098, 1122, 1148, 1176, 1206, 1238, 1273, 1311, 1352, 1396, 1444, 1497, 1555, 1618, 1687, 1764, 1850, 1945, 2053, 2174, 2311, 2469, 2652, 2866, 3119, 3424, 3797, 4264, 4866, 5670, 6796, 8488, 11309, 16956, 33902, 65535,
//    },
//    {
//        896, 896, 897, 898, 900, 902, 905, 909, 913, 918, 923, 929, 936, 943, 951, 960, 969, 980, 991, 1003, 1015, 1029, 1044, 1060, 1077, 1095, 1115, 1136, 1159, 1183, 1209, 1237, 1267, 1299, 1334, 1371, 1412, 1456, 1504, 1556, 1612, 1674, 1742, 1817, 1900, 1992, 2095, 2211, 2341, 2489, 2659, 2856, 3086, 3359, 3687, 4089, 4592, 5240, 6106, 7319, 9141, 12179, 18260, 36509, 65535,
//    },
//    {
//        960, 960, 961, 962, 964, 967, 970, 974, 978, 983, 989, 996, 1003, 1011, 1019, 1028, 1039, 1050, 1061, 1074, 1088, 1103, 1119, 1136, 1154, 1174, 1195, 1217, 1241, 1267, 1295, 1325, 1357, 1392, 1429, 1469, 1513, 1560, 1611, 1667, 1727, 1794, 1867, 1947, 2036, 2135, 2245, 2368, 2508, 2667, 2849, 3060, 3307, 3599, 3950, 4381, 4920, 5615, 6542, 7842, 9794, 13049, 19564, 39117, 65535,
//    },
//    {
//        1024, 1024, 1025, 1026, 1028, 1031, 1035, 1039, 1044, 1049, 1055, 1062, 1070, 1078, 1087, 1097, 1108, 1120, 1132, 1146, 1161, 1176, 1193, 1212, 1231, 1252, 1274, 1298, 1324, 1352, 1382, 1413, 1448, 1485, 1524, 1567, 1614, 1664, 1718, 1778, 1843, 1914, 1991, 2077, 2172, 2277, 2395, 2526, 2675, 2845, 3039, 3264, 3527, 3839, 4214, 4673, 5248, 5989, 6978, 8365, 10447, 13919, 20869, 41725, 65535,
//    },
//};

int main()
{
    GameMap gameMap;
//    constexpr uint8_t halfFov = 40;
//
//
//    uint8_t theta = 40;
//    uint8_t posX = 128;
//    uint8_t posY = 128;


//    double posX = 1;
//    double posY = 1;
//    double dirX = -1;
//    double dirY = 0;
//    double planeX = 0;
//    double planeY = 0.66;
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "piotoor's raycaster");
    window.setFramerateLimit(100);

    while (window.isOpen())
    {
        window.clear(sf::Color(40, 40, 40));
        window.clear();
////        cout << "theta = " << (int)theta << endl;
//        for (int w = 0; w < screenWidth; ++w) {
//            uint8_t mapX = posX / squareSize;
//            uint8_t mapY = posY / squareSize;
//            uint8_t stepX = 0;
//            uint8_t stepY = 0;
//
//            uint16_t dx = 0;
//            uint16_t dy = 0;
//            uint16_t initDistX = 0;
//            uint16_t initDistY = 0;
//
//            uint8_t rayTheta = theta + halfFov - 2 * w;
//            uint8_t indirRayTheta = rayTheta;
////            cout << "w = " << w << "--------------------------" << endl;
////            cout << "rayTheta = " << (int)rayTheta << endl;
////            cout << "indirRayTheta = " << (int)indirRayTheta << endl;
//            if (rayTheta >= 64 and rayTheta < 128) {
//                indirRayTheta = 128 - rayTheta;
//            } else if (rayTheta >= 128 and rayTheta < 192) {
//                indirRayTheta = rayTheta - 128;
//            } else if (rayTheta >= 192 and rayTheta < 256) {
//                indirRayTheta = 256 - rayTheta;
//            }
//
//            if (rayTheta >= 64 and rayTheta < 192) {
//                stepX = -1;
//                initDistX = cosTable[posX - squareSize * (posX / squareSize)][indirRayTheta];
//            } else {
//                stepX = 1;
//                initDistX = cosTable[squareSize * (posX / squareSize + 1) - posX][indirRayTheta];
//            }
//
//            if (rayTheta >= 0 and rayTheta < 128) {
//                stepY = 1;
//                initDistY = sinTable[posY - squareSize * (posY / squareSize) - 1][indirRayTheta];
//
//            } else {
//                stepY = -1;
//                initDistY = sinTable[squareSize * (posY / squareSize + 1) - posY - 1][indirRayTheta];
//            }
//
//            dx = cosTable[squareSize - 1][indirRayTheta];
//            dy = sinTable[squareSize - 1][indirRayTheta];
//
//            bool hit = false;
//            bool horizontal = false;
//
//            while (not hit) {
//                if (initDistX <= initDistY) {
//                    horizontal = true;
//                    initDistX += dx;
//                    mapX += stepX;
//                } else {
//                    horizontal = false;
//                    initDistY += dy;
//                    mapY += stepY;
//                }
//                if (gameMap[mapX][mapY] > 0) {
//                    hit = true;
//                }
//            }
//
////            cout << "initDistX = " << initDistX << endl;
////            cout << "initDistY = " << initDistY << endl;
////            cout << "dx = " << dx << endl;
////            cout << "dy = " << dy << endl;
//            // hack
//            initDistX = fmax((uint16_t)1, initDistX);
//
//            initDistY = fmax((uint16_t)1, initDistY);
//            //
//
//            uint16_t maxInitDist = (int)max(initDistX, initDistY);
//            maxInitDistX = fmax(maxInitDist, maxInitDistX);
//            uint16_t alpha = abs(theta - rayTheta);
//            uint8_t indirAlpha = alpha;
//
//            if (alpha >= 64 and alpha < 128) {
//                indirAlpha = 128 - alpha;
//            } else if (alpha >= 128 and alpha < 192) {
//                indirAlpha = alpha - 128;
//            } else if (alpha >= 192 and alpha < 256) {
//                indirAlpha = 256 - alpha;
//            }
//
//            uint16_t perpDist = maxInitDist * cos(indirAlpha * M_PI / 128);
//            cout << "-----------------" << endl;
//            cout << "perpDist = " << perpDist << endl;
//            cout << "maxInitDist = " << maxInitDist << endl;
//            cout << "ratio = " << perpDist * 1.0 / maxInitDist << endl;
//            int k = 0xFFFF / screenHeight; // 1638
//            int lineHeight = screenHeight - 12 * perpDist / k;
////            cout << "lineHeight = " << lineHeight << endl;
//            int lineStart = max(0, screenHeight / 2 - lineHeight / 2);
//            int lineEnd = min(screenHeight / 2 + lineHeight / 2, screenHeight - 1);
//
//
//            sf::VertexArray line(sf::Lines, 2);
//            sf::Color color = sf::Color::Red;
//            line[0].position = sf::Vector2f(w, lineStart);
//            line[1].position = sf::Vector2f(w, lineEnd);
////            cout << "w = " << w << "--------------------------" << endl;
////            cout << "line[0] = " << line[0].position.x << ", " << line[0].position.y << endl;
////            cout << "line[1] = " << line[1].position.x << ", " << line[1].position.y << endl;
//
//            if (horizontal) {
//                color.a = color.a / 2;
//            }
//
////            double colorModifier = max(1.0, (double)screenHeight / (double)lineHeight);
////
////            color.a /= colorModifier;
//
//            line[0].color = color;
//            line[1].color = color;
//            window.draw(line);
//
//
//        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time elapsed = clock.restart();

        window.display();
//
//        double moveSpeed = elapsed.asMilliseconds() / 1000.0 * 5.0;
//        double rotateSpeed = elapsed.asMilliseconds() / 1000.0 * 3.0;
//

//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
//            theta++;
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
//            theta--;
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//            break;
//        }
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//
//        }
//
//
    }
//
//    cout << "maxinitDistX = " << maxInitDistX << endl;
//
//    int k;
//    cin >> k;

    return 0;
}
