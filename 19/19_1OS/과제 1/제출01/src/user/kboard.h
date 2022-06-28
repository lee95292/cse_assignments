long kboard_copy(int clip){
        long res=syscall(335,clip);
        return res;

}

long kboard_paste(int *clip){
        long res=syscall(336,clip);

        return res;
}
