import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Scanner;

public class Transaction {
    private ArrayList<Product> orders;
    private LocalDateTime orderTime;
    private int totalPrice;

    public Transaction() {
        orders = new ArrayList<>();
        orderTime = LocalDateTime.now();
        totalPrice = 0;
    }

    public void addOrder(Product order) {
        orders.add(order);
    }

    public void removeOrder(int index) {
        orders.remove(index);
    }

    public Product getOrder(int index) {
        return orders.get(index);
    }

    public int getProductCount() {
        return orders.size();
    }

    public void printReceipt() {
        orderTime = LocalDateTime.now();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String receipt = new String();
        totalPrice = 0;

        receipt += "\n================== Pesanan ==================\n";
        receipt += "Waktu Pesanan: " + orderTime.format(formatter) + "\n";
        receipt += "=============================================\n";
        receipt += "#\tNama Produk\tQty\tHarga\tTotal Harga\n";

        for (int i = 0; i < orders.size(); i++) {
            Product p = orders.get(i);
            int productTotalPrice = p.getPrice() * p.getStock();
            totalPrice += productTotalPrice;
            receipt += (i + 1) + "\t" + p.getName() + "\t" + p.getStock() + "\t" + p.getPrice() + "\t" + productTotalPrice + "\n";
        }

        receipt += "=============================================";
        receipt += "\nTotal: \t\t\t" + totalPrice + "\n";
        receipt += "=============================================";
        System.out.println(receipt);
    }

    public void pay(Scanner scanner) {
        printReceipt();
        int money = 0;
        boolean isPaying = true;
        while(isPaying) {
            System.out.print("Masukkan Uang (0 untuk cancel): ");
            int inputMoney = scanner.nextInt();
            if(inputMoney <= 0) {
                System.out.println("Terimakasih telah mengunakan Monster Mart");
                if(money >= 0) System.out.println("Uang sebesar " + money + " telah dikembalikan");
                isPaying = false;
                break;
            } else money += inputMoney;
            if(totalPrice <= money) {
                System.out.println("Pembayaran anda berhasil");
                if(money - totalPrice != 0) System.out.println("Kembalian anda: " + (money - totalPrice));
                isPaying = false;
                break;
            } else System.out.println("Uang kurang" + (totalPrice - money) + ", silahkan masukkan uang lagi");
        }
    }
}