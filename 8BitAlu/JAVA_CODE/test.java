package tusharLogisim;

public class test {
    public static void main(String[] args) {
        int b = 0b10001111;
        int a = 0b01;

        a = (a << 24) >> 24;
        b = (b << 24) >> 24;

        int res = b >>> a;
        if(b < 0){
            int p = 0x000000FF;
            p = p >>> a;
            res = p & res;
        }

        System.out.println(Integer.toBinaryString(res));

    }
}
