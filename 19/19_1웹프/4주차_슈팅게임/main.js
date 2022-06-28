var context;
var dx = 15;        //초기 속도
var dy = 15;

var y = 100;        //초기 좌표
var x = 100;

let xlen=960;       //캔버스 크기
let ylen=1320;

let level=1;
let mouseX=0;

let radius=45;
let barSize=0;

let interval=50;
var time=0;
let duration=0


var canvas = document.getElementById('myCanvas');
var context = canvas.getContext('2d');
context.font='san-serif 15px Arial';

start=setInterval(draw, interval);
canvas.addEventListener("mousemove",onMouseUp,false);

function draw() {
    context.clearRect(0, 0, xlen, ylen);                //원 그리기 시작
    context.beginPath();
    context.fillStyle = "red";
    context.arc(x, y, radius, 0, Math.PI * 2, true);
    context.closePath();
    context.fill();
    x += dx;
    y += dy;
    if (x < (radius+Math.abs(dx)) || x > (xlen - (radius+Math.abs(dx))))        //벽에 부딛힘.
        dx = -dx;
    if(y < (radius+Math.abs(dy)))      
        dy = -dy;
        
    if (y > (ylen - (radius+Math.abs(dy)))){            //game over 조건
        console.log('game over');
        context.fillText("game over",xlen/2,ylen/2);
        return;
    }

    if(y>ylen-200-Math.ceil(dy/2)-radius&&y<ylen-200+Math.ceil(dy/2)
        &&x<=mouseX+barSize/2&&x>mouseX-barSize/2){  //바에 부딛힘
            dy=-dy;
    }

    time+=interval;
    if(time>1000){                          //시간을 1초씩 증가시키는 코드
        duration+=Math.round(time/1000);
        time=0;
    }

    if(level<1+Math.floor(Math.sqrt(duration/10))){     //레벨 증가시키기
        level++;
        interval-=10;
    }
    barSize=200-level*10;
    context.beginPath();
    context.fillStyle="green";
    context.rect(mouseX-barSize/2,ylen-200,barSize,40);
    context.fill();


    context.font='italic 30pt Arial';
    context.fillStyle="black";
    context.fillText('Duration:'+duration,xlen-300,ylen-20);
    context.fillText('Level:'+level,xlen-600,ylen-20);
    //this.canvas.onmousemove(e){}
}    

function onMouseUp(e){
    mouseX=e.clientX;
}