#include <iostream>
#include <vector>
using namespace std;

int count = 0;
bool isNonDirectGraph(const vector<vector<bool>> & G) {
    for (int i = 0; i < G.size(); ++i)
            for (int j = 0; j <  i; ++j)
                if (G[i][j] != G[j][i])
                    return false;
    return true;
}

void deg(const vector<vector<bool>> & G, vector<int> & deg_G) {
    for (int i = 0; i < G.size(); ++i) {
        int Deg = 0;
        for (int j = 0; j < G.size(); ++j)
            Deg += G[i][j];
        deg_G[i] = Deg;
    }
}

bool isomorphic(const vector<vector<bool>> & G1,
                const vector<vector<bool>> & G2,
                const int & solving , const int Size,
                vector<int> & preimage,
                vector<int> & image,
                vector<int> & deg_preimage,
                vector<int> & deg_image) {
    if (solving == Size) {
        return true;
    }
    for (int i = 0; i < Size; ++i) {
        if (image[i] == -1 && deg_image[solving] == deg_image[i]) {
            preimage[solving] = i;
            image[i] = solving;
            bool valid = true;
            for (int j = 0; j < solving; ++j) {
                if (G1[j][solving] != G2[preimage[j]][preimage[solving]] || G1[solving][j] != G2[preimage[solving]][preimage[j]]) {
                    valid = false;
                    break;
                }
            }
            if (valid)
                if (isomorphic(G1, G2, solving + 1, Size, preimage, image, deg_preimage, deg_image))
                    return true;
            preimage[solving] = -1;
            image[i] = -1;
        }
    }
    return false;
}

bool isIsomorphic(const vector<vector<bool>> & G1, const vector<vector<bool>> & G2) {
    if (G1.empty() || G1[0].empty() || G1.size() != G2.size() || G1.size() != G1[0].size() || G2.size() != G2[0].size())
        return false;
    if (!isNonDirectGraph(G1) || !isNonDirectGraph(G2))
            return false;
    const int Size = static_cast<int> (G1.size());

    vector<int> preimage(Size, -1);
    vector<int> image(Size, -1);

    vector<int> deg_preimage(Size, 0);
    vector<int> deg_image(Size, 0);
    deg(G1, deg_preimage);
    deg(G2, deg_image);

    return isomorphic(G1, G2, 0, Size, preimage, image, deg_preimage, deg_image);
}

int main(int argc, const char * argv[]) {

    vector<vector<bool>> G1 = {/* Fill graph 1 */};

    vector<vector<bool>> G2 = {/* Fill graph 1 */};

    // Check
    if (isIsomorphic(G1, G2))
        cout << boolalpha << true << endl;
    else
        cout << boolalpha << false << endl;
    return 0;
}