#include <vector>
#include <iostream>
#include <string>
//// MASA HASSAN ADEL 11923986
using namespace std;
#define COUNT 10
class Node {
public:
char data;
    vector <Node*> children;
    Node() {};
    Node(char data) { this->data = data; };
  
    

     void InsertString(Node *root, char* s,int stringLength,int count) {
         // count at first is arr length then start decreasing 
       
         if (count ==0) {
           
                    InsertChar(root, '$');
                
          //   printf("add $\n");
             return;
         }
       
         int idx = stringLength - count;
       
         count--;
         bool flag = false;

         if (root->children.empty())
         {
             InsertChar(root, s[idx]);
             InsertString(root->children[0], s, stringLength, count);
          }

         else if (!root->children.empty() ) {
              for (size_t k = 0; k < root->children.size(); k++) {
                 if ((root->children[k]->data) == s[idx]) {
                      flag = true;
                     InsertString(root->children[k], s, stringLength, count);
                   //dont insert it
                }
               }
             if (flag == false) {
                // printf("hfft");
               //  printf("index is %d, data is %c parent is %c\n", idx, s[idx], root->data);

                 InsertChar(root, s[idx]);
                 InsertString(root->children[root->children.size()-1], s, stringLength, count);
             }
         }

      }

//________________________________________________________________________
     void InsertChar(Node* root, char c) {
         root->children.push_back(new Node(c));
     //   printf("reached\n");
         
     }
  
    
 
   
     

   bool searchFlag = false;
   void  Search(Node *root,char* s ,size_t arrLength,size_t idx) {
        // searchFlag = false;
       searchFlag = false;
       for (size_t i = 0; i < root->children.size(); i++) {
           
           if (root->children[i]->data == s[idx]){
               if (idx == (arrLength - 1)) {
                 
                    for(size_t k=0; k< root->children[i]->children.size();k++){
                    if(root->children[i]->children[k]->data == '$'){
                       
                       searchFlag = true;
                       return;
                    }
                    
                    }
                }
                idx++;
                Search(root->children[i], s, arrLength, idx);
                  
           } 
         }
       

   }
 /********           STARTTS WITH       *********/
   void startsWith(Node *root, char *s, size_t arrLength, size_t idx) {
      // if (idx == arrLength) return;
       for (size_t i = 0; i < root->children.size(); i++) {
           if (root->children[i]->data == s[idx]) {
               if (idx == arrLength - 1) {
                  
                   findStartWith(root->children[i],s);
                    printStartWithInOrder();
                   return;
               }
               idx++;
               startsWith(root->children[i], s, arrLength, idx);
           }
       }
   
   }
 vector <string> starttt;
    void findStartWith(Node* root, string parentPath) {

        for (size_t k = 0; k < root->children.size(); k++) {
            string currPath = parentPath + root->children[k]->data;
           
            if ((root->children[k]->data == '$') ) {
                currPath.pop_back();// remove $
                starttt.push_back(currPath);
                
            }
            else findStartWith(root->children[k], currPath);
        }
       
    }
    
   void printStartWithInOrder() {
        starttt = sort(starttt, starttt.size());
        for (size_t k = 0; k < starttt.size(); k++) {
            cout << starttt[k] << endl;
        }
        starttt.clear();
    }
    vector<string> sort(vector<string> s, size_t n)
    {

        for (size_t i = 1; i < n; i++)
        {

            string temp = s[i];

            // Insert s[j] at its correct position
            int j = i - 1;
            while (j >= 0 && isAlphaSmaller(temp, s[j]))
            {
                s[j + 1] = s[j];
                j--;
            }
            s[j + 1] = temp;
        }
        return s;
    }



    
    bool isAlphaSmaller(string s1, string s2) {
        size_t sizex = s1.length() > s2.length() ? s2.length() : s1.length();//smaller
        for (size_t i = 0; i < sizex; i++) {
            if (i == sizex - 1) {
                if (s1[i] == s2[i]) {
                    if (s1.length() < s2.length())
                        return true;
                  //  else return false;
                }
            }
            
            {
             if (s1[i] < s2[i]) return true;
              else if (s1[i] == s2[i]) continue;
                else return false;
        }}
        return false;
    }
   /********    END       STARTTS WITH    END   *********/


 
/**     LONGEST      **/

    vector<char> Get_Max_Path(Node* root)
    {
        if (root->data == '$')  return vector <char>(0);
        vector<vector<char>> vec;
        for (size_t k = 0; k < root->children.size(); k++) {
            
            vec.push_back(GetPath(root, Get_Max_Path(root->children[k])));

        }
        return Max_Path( vec);
    }
    vector<char> GetPath(Node* N, vector<char> v)
    {
        v.push_back(N->data);
        return v;
    }
    vector<vector<char>> publicVec;
    vector<char> Max_Path(vector<vector<char>> vec)
    {
        
        //publicVec = vec;
        size_t count = 0;
        vector<char> tmp;
        for (size_t k = 0; k < vec.size(); k++) {
            if (vec[k].size() >= count) {

                tmp.clear();
                tmp = vec[k];
                count = vec[k].size();
            }
        }

        return tmp;
    }

/**          END OF LONGEST   **/

     /*     -----------------------------------------------    */
     /*         STARTS DELETE          */
  void deleteStringMain(Node* root ,char* s,size_t length) {
      Search(root, s, length, 0);
      if (searchFlag == true) {
          deleteStringFunc(root, s, length,0);
      }
   }

  void deleteChild(Node* root, char data) {
        int counter = 0;
        Node* tmpNode;
        vector <Node*> tmp;
        for (size_t k = 0; k < root->children.size(); k++) {
            if (root->children[k]->data == data) { 
                counter++; 
                tmpNode = root->children[k];
            }//do nothing

            else  tmp.push_back(root->children[k]);
            //deleteChild(root, i-1);
        }
        counter--;
        if (counter > 0) {
            while (counter > 0) {
                tmp.push_back(tmpNode);
                counter--;
            }
        }
        root->children.clear();
        
        root->children = tmp;
        // printf("reached deleted %c\n", data);

    }
  bool stop;
  bool deleteStringFunc(Node* root, char* s, size_t length,size_t idx) {
       stop = false;
       for (size_t i=0;i< root->children.size();i++){
             if (root->children[i]->data == s[idx]) {
                if (deleteStringFunc(root->children[i], s, length, idx + 1)) {
                    if (stop == false) {
                        deleteChild(root, s[idx]);
                    }
                    if (root->children.size() == 0) return true;
                    else
                    {
                        stop = true;
                        return false;
                    }
                }
             }
           // cout << "kk" << root->children[i]->data << "idx==" << idx << endl;
           if ((root->children[i]->data == '$')&& (idx==length)) {
              deleteChild(root, '$');
              if (root->children.empty())
                   return true;
              else {
                  stop = true;
                  return false; }
           }
           
          }
          return stop;
  }
  /*         END DELETE          */
   /*     --------------------------------------------------------------    */
    
  
};

vector<string> splitSpace(string cmd) {
    vector<string> out;
    string tmpWord = "";
    for (size_t i = 0; i <= cmd.size();i++) {
       char x = cmd[i];
      
        if ((x == ' ')||(i== cmd.size())) {
            out.push_back(tmpWord);
          tmpWord = "";
        }
            
        else
            tmpWord = tmpWord + x;
    }
    return out;
}

int main() {
    /*   main root*/
    Node* root = new Node('*');
    /*   main root*/
  
    
   string cmd;
   vector<string> cmdWords;
   string cmdWord;
   string input;

  // int iterationsCount;
  // scanf("%d", &iterationsCount);
   string iter;
   getline(cin, iter);
   for (int i=0;i< stoi(iter); i++) {
        getline(cin, cmd);  
        if (cmd == "longest") {
             vector<char> vecoflongest = root->Get_Max_Path(root);
             size_t vecSize = vecoflongest.size();
             for (size_t m = 1; m < vecSize; m++) printf("%c", vecoflongest[vecSize - m - 1]);
             printf("\n");
        }

        else{
        cmdWords = splitSpace(cmd);
        cmdWord = cmdWords[0];
        input = cmdWords[1];
        char* arr = &input[0];

          if (cmdWord == "insert") {
              root->InsertString(root, arr, (int)input.length(), (int)input.length());
          }
          else if (cmdWord == "search") {
              root->Search(root, arr, (int)input.length(), 0);

              if (root->searchFlag == true) printf("YES\n"); else  printf("NO\n");
             
          }
          else if (cmdWord == "delete") {
               root->Search(root, arr, input.length(), 0);
               root->deleteStringMain(root,arr, input.length());
          }
          else if (cmdWord == "startwith") {
              root->startsWith(root, arr, input.length(), 0);
          }
        }
   }
  
   
};
    
                           
