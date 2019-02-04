//Hikaru-5システムのai
//開発:正岡真一
//コマンドラインでpかlを選択

#include <stdio.h>
#include <time.h>

#define O 1
#define X 2
#define EMPTY 0
#define UNKNOWN 4
#define OUTER 5

#define X_MAX 9
#define Y_MAX 9

#define MARGIN 7

#define BOARD_WIDTH X_MAX+MARGIN*2
#define BOARD_HEIGHT Y_MAX+MARGIN*2

#define JUDGE_ARRAY_SIZE X_MAX*Y_MAX

#define DEPTH 2

#define TYPE1_VAL 10//xoo-
#define TYPE2_VAL 15//xooo-
#define TYPE3_VAL 20//xoooo-
#define TYPE4_VAL 15//-oo-
#define TYPE5_VAL 3000//-ooo-
#define TYPE6_VAL 100000//-oooo-
#define TYPE8_VAL 100000//check
#define TYPE9_VAL 10000000//goal

void find_pattern(int turn,int buf[2][128],int empty,int pos,int pattern_counter[5][2]);
int judge(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height);
void ai(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height,int depth);
int min(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height,int alpha,int beta,int depth);
int max(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height,int alpha,int beta,int depth);
int is_judge_or_not(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int pos_x,int pos_y);
void get_judge_array(int turn,int fld[BOARD_WIDTH][BOARD_WIDTH],int width,int height,int dist_array[JUDGE_ARRAY_SIZE][2],int *n);

int main(int argc, char *argv[]){
    clock_t t1, t2;
    
    int fld[BOARD_WIDTH][BOARD_HEIGHT]={
        //1,2,3,4,5,6,7 ,1,2,3,4,5,6,7,8,9 ,1,2,3,4,5,6,7
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//1
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//2
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//3
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//4
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//5
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//6
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//7
        
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//1
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//2
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//3
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//4
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//5
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//6
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//7
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//8
        {5,5,5,5,5,5,5 ,0,0,0,0,0,0,0,0,0 ,5,5,5,5,5,5,5},//9
        
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//1
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//2
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//3
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//4
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//5
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//6
        {5,5,5,5,5,5,5 ,5,5,5,5,5,5,5,5,5 ,5,5,5,5,5,5,5},//7
    };
    
    int i,j;
    int x,y;
    
    int turn;
    int te;
    if(*argv[1]=='p')turn=1,te=O;
    if(*argv[1]=='l')turn=2,te=X;
    
    int width=X_MAX;
    int height=Y_MAX;
    
    //ゲームフロー
    for(;;){
        //AIの手番
        if(turn==1){
            t1 = clock();
            ai(te,fld,width,height,DEPTH);
            t2 = clock();
            printf("time:%f[sec]\n",(double)(t2-t1)/CLOCKS_PER_SEC);
        }
        
        //playerの手番
        if(turn==2){
            printf("you:");
            scanf("%d,%d",&x,&y);
            while(fld[y+MARGIN-1][x+MARGIN-1]!=0){
                printf("*again->enemy:");
                scanf("%d,%d",&x,&y);
            }
            fld[y+MARGIN-1][x+MARGIN-1]=3-te;
        }
        printf("  1 2 3 4 5 6 7 8 9\n");
        for(i=MARGIN;i<MARGIN+width;i++){
            printf("%d ",i-MARGIN+1);
            for(j=MARGIN;j<MARGIN+height;j++){
                if(fld[i][j]==0)printf("- ");
                if(fld[i][j]==1)printf("o ");
                if(fld[i][j]==2)printf("x ");
            }
            printf("\n");
        }
        printf("~~~~~~~~~~~~~~~~~~~~~\n");
        
        //後処理
        turn=3-turn;
        if(judge(1,fld,width,height)>=10000000){
            printf("I won.\n");
            break;
        }
        if(judge(2,fld,width,height)>=10000000 || fld[0][0]==te){
            printf("I lose.\n");
            break;
        }
    }
    
    return 0;
}

//judge関数から探索開始位置を引数に受けて何個石が繋がってるか数える
void find_pattern(int turn,int buf[2][128],int empty,int pos,int pattern_counter[5][2]){
    int counter=0;
    int skip_counter=0;
    int end_pos=0;
    int type=0;
    int counter_buf_when_skip=0;
    int type_buf_when_skip=0;
    
    for(int i=0;i<5;i++){
        if(buf[0][pos-i]==turn){
            counter++;
            end_pos=pos-i;
        }
        //-o-oo-なども飛び三として数える。対称性を持たせるために合間の-oo-を二として重複して数える
        else if(buf[0][pos-i]==EMPTY){
            if(skip_counter==0){
                skip_counter=1;
                if(empty-1>=(5-(pos-end_pos+1))){
                    type++;
                }
                if(buf[1][end_pos]-1>=(5-(pos-end_pos+1))){
                    type++;
                }
                
                if(type>0){
                    counter_buf_when_skip=counter-1;
                    type_buf_when_skip=type-1;
                }
                type=0;
            }
            //ただし、-o--oo-や-o-o-o-など穴が2つは認めない
            else if(skip_counter==1){
                break;
            }
        }
        //壁や敵石に当たったら終わり
        else if(buf[0][pos-i]==OUTER || buf[0][pos-i]==3-turn){
            break;
        }
    }
    
    //emptyは引数で受けた自石の左に何個スペースがあるか
    if(empty-1>=(5-(pos-end_pos+1))){
        type++;
    }
    //buf[1][]は自石の右に何個スペースがあるかのバッファ
    if(buf[1][end_pos]-1>=(5-(pos-end_pos+1))){
        type++;
    }
    
    //5-((自石の並ぶ個数)+(飛びの数=0or1))=5連に必要な条件
    //両方に伸ばせるか、片方に伸ばせるかによって価値が違う
    if(counter_buf_when_skip!=counter-1 && type_buf_when_skip!=type-1){
        pattern_counter[counter_buf_when_skip][type_buf_when_skip]++;
    }
    if(type>0){
        pattern_counter[counter-1][type-1]++;
    }
}

//盤面評価関数
//2次元配列を4方向*1次元に直してから、順方向に石を数えて、自石の左側に何個空白があるかをバッファに格納していく
//次に逆順に探索して、自石の右側に何個空白があるかを数えながら、何個自石が並んでるかを数える
int judge(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height){
    int buf[2][128]={};
    int counter;
    int empty_counter=0;
    int value=0;
    int pattern_counter[5][2]={};
    
    //横
    counter=0;
    empty_counter=0;
    for(int i=MARGIN;i<MARGIN+height;i++){
        for(int j=MARGIN-1;j<MARGIN+width+1;j++){
            buf[0][counter]=fld[j][i];
            if(counter !=0 && (fld[j][i]==EMPTY || fld[j][i]==turn)){
                buf[1][counter]=buf[1][counter-1]+1;
            }else{
                buf[1][counter]=0;
            }
            counter++;
        }
    }
    for(int i=counter-1;i>0;i--){
        if(buf[0][i]==turn || buf[0][i]==EMPTY){
            empty_counter++;
        }
        else if(buf[0][i]==OUTER || buf[0][i]==3-turn){
            empty_counter=0;
        }
        if(buf[0][i]==turn && buf[0][i+1]!=turn){
            find_pattern(turn,buf,empty_counter,i,pattern_counter);
        }
    }
    
    
    //縦
    counter=0;
    empty_counter=0;
    for(int i=MARGIN;i<MARGIN+width;i++){
        for(int j=MARGIN-1;j<MARGIN+height+1;j++){
            buf[0][counter]=fld[i][j];
            if(counter !=0 && (fld[i][j]==EMPTY || fld[i][j]==turn)){
                buf[1][counter]=buf[1][counter-1]+1;
            }else{
                buf[1][counter]=0;
            }
            counter++;
        }
    }
    for(int i=counter-1;i>0;i--){
        if(buf[0][i]==turn || buf[0][i]==EMPTY){
            empty_counter++;
        }
        else if(buf[0][i]==OUTER || buf[0][i]==3-turn){
            empty_counter=0;
        }
        if(buf[0][i]==turn && buf[0][i+1]!=turn){
            find_pattern(turn,buf,empty_counter,i,pattern_counter);
        }
    }
    
    //右上
    counter=0;
    empty_counter=0;
    for(int i=MARGIN+1;i<=MARGIN+height;i++){
        for(int j=MARGIN-1,k=0;i-k>MARGIN-2 && j<MARGIN+width+1;j++,k++){
            buf[0][counter]=fld[j][i-k];
            if(counter !=0 && (fld[j][i-k]==EMPTY || fld[j][i-k]==turn)){
                buf[1][counter]=buf[1][counter-1]+1;
            }else{
                buf[1][counter]=0;
            }
            counter++;
        }
    }
    for(int i=MARGIN;i<MARGIN+width-1;i++){
        for(int j=MARGIN+height,k=0;j>MARGIN-2 && i+k<MARGIN+width+1;j--,k++){
            buf[0][counter]=fld[i+k][j];
            if(counter !=0 && (fld[i+k][j]==EMPTY || fld[i+k][j]==turn)){
                buf[1][counter]=buf[1][counter-1]+1;
            }else{
                buf[1][counter]=0;
            }
            counter++;
        }
    }
    for(int i=counter-1;i>0;i--){
        if(buf[0][i]==turn || buf[0][i]==EMPTY){
            empty_counter++;
        }
        else if(buf[0][i]==OUTER || buf[0][i]==3-turn){
            empty_counter=0;
        }
        if(buf[0][i]==turn && buf[0][i+1]!=turn){
            find_pattern(turn,buf,empty_counter,i,pattern_counter);
        }
    }
    
    //右下
    counter=0;
    empty_counter=0;
    for(int i=MARGIN+width-2;i>=MARGIN-1;i--){
        for(int j=MARGIN-1,k=0;j<MARGIN+height+1 && i+k<MARGIN+width+1;j++,k++){
            buf[0][counter]=fld[i+k][j];
            if(counter !=0 && (fld[i+k][j]==EMPTY || fld[i+k][j]==turn)){
                buf[1][counter]=buf[1][counter-1]+1;
            }else{
                buf[1][counter]=0;
            }
            counter++;
        }
    }
    for(int i=MARGIN;i<=MARGIN+height-2;i++){
        for(int j=MARGIN-1,k=0;i+k<MARGIN+height+1 && j<MARGIN+width+1;j++,k++){
            buf[0][counter]=fld[j][i+k];
            if(counter !=0 && (fld[j][i+k]==EMPTY || fld[j][i+k]==turn)){
                buf[1][counter]=buf[1][counter-1]+1;
            }else{
                buf[1][counter]=0;
            }
            counter++;
        }
    }
    for(int i=counter-1;i>0;i--){
        if(buf[0][i]==turn || buf[0][i]==EMPTY){
            empty_counter++;
        }
        else if(buf[0][i]==OUTER || buf[0][i]==3-turn){
            empty_counter=0;
        }
        if(buf[0][i]==turn && buf[0][i+1]!=turn){
            find_pattern(turn,buf,empty_counter,i,pattern_counter);
        }
    }
    
    //盤面の中央に近いほどポイントを高くする
    for(int i=MARGIN;i<MARGIN+width;i++){
        for(int j=MARGIN;j<MARGIN+height;j++){
            for (int p = 1; p <= 9 / 2; p++){
                if ((i - MARGIN >= p && i - MARGIN <= width - p -1) && (j - MARGIN >= p && j - MARGIN <= height - p - 1) && fld[i][j] == turn){
                    value++;
                }
            }
        }
    }
    
    value+=pattern_counter[1][0]*TYPE1_VAL;
    value+=pattern_counter[2][0]*TYPE2_VAL;
    value+=pattern_counter[3][0]*TYPE3_VAL;
    value+=pattern_counter[1][1]*TYPE4_VAL;
    value+=pattern_counter[2][1]*TYPE5_VAL;
    value+=pattern_counter[3][1]*TYPE6_VAL;
    
    //三三、四四、四三の必勝系
    if((pattern_counter[3][0]>=1 && pattern_counter[2][1]>=1) || pattern_counter[3][0]>=2 || pattern_counter[2][1]>=2){
        value+=TYPE8_VAL;
    }
    
    value+=pattern_counter[4][0]*TYPE9_VAL;
    value+=pattern_counter[4][1]*TYPE9_VAL;
    
    return value;
}

//ここからただのalpha-beta法
void ai(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height,int depth){
    int n;
    int judge_array[JUDGE_ARRAY_SIZE][2];
    int i_buf=0,j_buf=0,val_buf=100000000,ans=-100000000;
    int alpha=-100000000,beta=100000000;
    
    //深さ1でソートかけておく
    get_judge_array(turn,fld,width,height,judge_array,&n);
    
    //初手は中央
    if(turn==1 && fld[(width+MARGIN*2)/2][(height+MARGIN*2)/2]==EMPTY && n==0){
        fld[(width+MARGIN*2)/2][(height+MARGIN*2)/2]=turn;
        printf("ai:%d,%d\n",(width+MARGIN*2)/2-MARGIN+1,(height+MARGIN*2)/2-MARGIN+1);
        return;
    }
    else{
        for(int i=0;i<n;i++){
            fld[judge_array[i][0]][judge_array[i][1]]=turn;
            if(TYPE9_VAL<judge(turn,fld,width,height)){
                i_buf=judge_array[i][0],j_buf=judge_array[i][1];
                printf("ai:%d,%d\n",j_buf-MARGIN+1,i_buf-MARGIN+1);
                return;
            }
            val_buf=min(turn,fld,width,height,alpha,beta,depth-1);
            fld[judge_array[i][0]][judge_array[i][1]]=EMPTY;
            if(alpha<val_buf){
                i_buf=judge_array[i][0],j_buf=judge_array[i][1];
                alpha=val_buf;
            }
        }
        
        fld[i_buf][j_buf]=turn;
        printf("ai:%d,%d\n",j_buf-MARGIN+1,i_buf-MARGIN+1);
    }
}

int min(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height,int alpha,int beta,int depth){
    int judge_buf;
    int n;
    int judge_array[JUDGE_ARRAY_SIZE][2];
    int val=1000000;
    
    get_judge_array(3-turn,fld,width,height,judge_array,&n);
    
    for(int i=0;i<n;i++){
        fld[judge_array[i][0]][judge_array[i][1]]=3-turn;
        if(TYPE9_VAL<judge(3-turn,fld,width,height)){
            fld[judge_array[i][0]][judge_array[i][1]]=EMPTY;
            beta=-1*TYPE9_VAL*(depth+1);
            return beta;
        }
        judge_buf=max(turn,fld,width,height,alpha,beta,depth);
        fld[judge_array[i][0]][judge_array[i][1]]=EMPTY;
        if(beta>judge_buf){
            beta=judge_buf;
        }
        if(beta<=alpha){
            return beta;
        }
        
    }
    return beta;
}

int max(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int width,int height,int alpha,int beta,int depth){
    int judge_buf;
    int n;
    int judge_array[JUDGE_ARRAY_SIZE][2];
    int val=-1000000;
    
    get_judge_array(turn,fld,width,height,judge_array,&n);
    
    for(int i=0;i<n;i++){
        fld[judge_array[i][0]][judge_array[i][1]]=turn;
        if(TYPE9_VAL<judge(turn,fld,width,height)){
            fld[judge_array[i][0]][judge_array[i][1]]=EMPTY;
            alpha=TYPE9_VAL*(depth+1);
            return alpha;
        }
        if(depth<=0){
            judge_buf=judge(turn,fld,width,height)-judge(3-turn,fld,width,height);
        }else{
            judge_buf=min(turn,fld,width,height,alpha,beta,depth-1);
        }
        fld[judge_array[i][0]][judge_array[i][1]]=EMPTY;
        if(alpha<judge_buf){
            alpha=judge_buf;
        }
        if(alpha>=beta){
            return alpha;
        }
        
    }
    return alpha;
}

//探索範囲を今置かれてる石から距離2の範囲に限定する
int is_judge_or_not(int turn,int fld[BOARD_WIDTH][BOARD_HEIGHT],int pos_x,int pos_y){
    for(int i=pos_x-2;i<pos_x+3;i++){
        for(int j=pos_y-2;j<pos_y+3;j++){
            if(fld[i][j]==turn || fld[i][j]==3-turn){
                return 1;
            }
        }
    }
    
    return 0;
}

void get_judge_array(int turn,int fld[BOARD_WIDTH][BOARD_WIDTH],int width,int height,int dist_array[JUDGE_ARRAY_SIZE][2],int *n){
    int buf[JUDGE_ARRAY_SIZE]={};
    int temp;
    int counter=0;
    
    for(int i=MARGIN;i<MARGIN+width;i++){
        for(int j=MARGIN;j<MARGIN+height;j++){
            if(is_judge_or_not(turn,fld,i,j)==1 && fld[i][j]==EMPTY){
                fld[i][j]=turn;
                buf[counter]=judge(turn,fld,width,height)-judge(3-turn,fld,width,height);
                dist_array[counter][0]=i;
                dist_array[counter][1]=j;
                counter++;
                fld[i][j]=EMPTY;
            }
        }
    }
    
    for(int i=0;i<counter;i++){
        for(int j=counter-1;j>i;j--){
            if(buf[j-1]<buf[j]){
                temp=buf[j-1];
                buf[j-1]=buf[j];
                buf[j]=temp;
                
                temp=dist_array[j-1][0];
                dist_array[j-1][0]=dist_array[j][0];
                dist_array[j][0]=temp;
                
                temp=dist_array[j-1][1];
                dist_array[j-1][1]=dist_array[j][1];
                dist_array[j][1]=temp;
            }
        }
    }
    
    *n=counter;
}
