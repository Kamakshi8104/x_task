#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class dot_info{
    public:
    dot_info* next;
    int line_no;
    vector<int> dot_pos;
    dot_info(int l){
        next=NULL;
        line_no=l;
    }

};
class dot_list{
 public:
 dot_info* head;
 dot_info* tail;
 dot_list(){
    head=NULL;
    tail=NULL;
 }
 void insert(dot_info* d){
    if(head==NULL){
        head=d;
        tail=d;
        return;
    }
    tail->next=d;
    tail=d;
 }
 void print(){
    dot_info* p=head;
    while(p!=NULL){
        cout<<p->line_no<<"  dots: ";
        for(int i=0;i<p->dot_pos.size();i++){
            cout<<p->dot_pos[i]<<" ";
        }
        cout<<endl;
        p=p->next;
    }
 }
};
class dot{
    public:
    int line;
    int pos;
    dot(int l,int p){
        line=l;
        pos=p;
    }
};
bool path_present(dot_info* p, int i){
    for(int j=0;j<p->dot_pos.size();j++){
        if(p->dot_pos[j]==i){
            return true;

        }


    }
    return false;
    

}
int path_pos(dot_info* p, int i){
    for(int j=0;j<p->dot_pos.size();j++){
        if(p->dot_pos[j]==i){
            return j;

        }


    }
    return -1;

}

vector<dot> path(dot_list l,dot_info* p,int i ,bool frm_right, bool frm_left){
    vector<dot> ans;


    if(p==NULL){
        return ans;

    }
    dot d(p->line_no,p->dot_pos[i]);
    ans.push_back(d);
    vector<dot> left;
    vector<dot> right;
    vector<dot> down;
    vector<dot> diag_left;
    vector<dot> diag_right;

    if(i<(p->dot_pos.size()-1) && (p->dot_pos[i+1]-p->dot_pos[i])==1 && frm_right==false){
        right=path(l,p,i+1,false,true);
        
    }
    
    if(i>0 && (p->dot_pos[i]-p->dot_pos[i-1])==1 && frm_left==false){
        left=path(l,p,i-1,true,false);
    }
    if(p->next!=NULL && path_present(p->next,p->dot_pos[i])){
        int x=path_pos(p->next,p->dot_pos[i]);
        down=path(l,p->next,x,false,false);
    }
    if(p->next!=NULL && path_present(p->next,p->dot_pos[i]-1)){
        int x=path_pos(p->next,p->dot_pos[i]-1);
        diag_left=path(l,p->next,x,false,false);
    }
    if(p->next!=NULL && path_present(p->next,p->dot_pos[i]+1)){
        int x=path_pos(p->next,p->dot_pos[i]+1);
        diag_right=path(l,p->next,x,false,false);
    }
    if(left.size()==0 && right.size()==0 && down.size()==0 && diag_left.size()==0 && diag_right.size()==0){
        return ans;
    }
    vector<dot> smallans;

    if(right.size()<left.size()){
        int s=left.size()-1;
        if(s>=0 && left[s].line==l.tail->line_no){
            smallans=left;
        }
        
    }
    else{
        int s=right.size()-1;
        if(s>=0 && right[s].line==l.tail->line_no){
            smallans=right;
        }
    }
    if(smallans.size()<=down.size()){
        smallans=down;
    }
    if(smallans.size()<=diag_left.size()){
        smallans=diag_left;
    }
    if(smallans.size()<=diag_right.size()){
        smallans=diag_right;
    }
    for(int k=0;k<smallans.size();k++){
        ans.push_back(smallans[k]);
    }
    return ans;

    




}
vector<dot> get_largest(dot_list l){
    dot_info* h=l.head;
    int prev=-1;
    int max_size=0;
    vector<dot> ans;
    
    for(int i=0;i<h->dot_pos.size();i++){
        
        
            vector<dot> v=path(l,l.head,i,false,false);
            
            //cout<<v[s].line<<endl;
            //cout<<l.tail->line_no<<endl;

            if(max_size<v.size()){
                max_size=v.size();
                ans=v;

            }

            
        
        

    }
    return ans;
}











int main() {
    // Open the file
    ifstream file("labryinth.txt");


    // Check if the file is open
    if (!file.is_open()) {
        cout << "Unable to open the file." << endl;
        return 1; // Return an error code
    }
    string line;
    int lineNumber = 1;
    dot_list l;

    while (getline(file, line)) {
        // Process each character in the line
        dot_info* new_line=new dot_info(lineNumber);
        l.insert(new_line);
        


        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == '.') {
                new_line->dot_pos.push_back(i);
                
            }
        }
        
        lineNumber++;
    }
    file.close();
    
    l.print();
    bool is_path=true;
    vector<dot> ans=get_largest(l);
    for(int i=0;i<ans.size();i++){
        dot d=ans[i];
        cout<<d.line<<" "<<d.pos<<endl;
    }
    int last=ans.size()-1;
    dot last_dot=ans[last];
    if(last_dot.line<l.tail->line_no){
        cout<<-1<<endl;
        is_path=false;
        
    }
    else{
     cout<<ans.size()<<endl;
    }
    ofstream outputFile("path.txt");
    ifstream inputfile("labryinth.txt");
    // Check if the file is open
    if (!outputFile.is_open()) {
        cout << "Unable to open the file." << endl;
        return 1; // Return an error code
    }
    
    if(is_path==false){
        outputFile<<-1<<endl;
        string s;
        while(getline(inputfile,s)){
            outputFile<<s<<endl;
        }
    }
    else{
        string s;
        outputFile<<ans.size()<<endl;
        int line=1;
        int path_step=0;


        
        while(getline(inputfile,s)){
            while(line==ans[path_step].line){
                int p=ans[path_step].pos;

                s[p]=char(path_step+48);
                path_step++;
            }
            line++;
            outputFile<<s<<endl;
        }


    }
    outputFile.close();
    file.close();


    
    
}


