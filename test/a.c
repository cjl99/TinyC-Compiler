int main(){
    int i = 0;
    int a = 0;
    for(;a<100;i++){
        a++;
        if(a==2) {
            a++;
            if(a==3){
                a += 2;
                break;
            }
            a++;
        }
        a--;
    }
    a = 1;
    return 0;
}
