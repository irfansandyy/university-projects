import java.util.ArrayList;
import java.util.Scanner;

public class VendingMachine {
    private ArrayList<Product> products;
    private ArrayList<Transaction> transactions;

    public VendingMachine() {
        this.products = new ArrayList<>();
        this.transactions = new ArrayList<>();
        initializeProducts();
    }

    public static void main(String[] args) {
        VendingMachine monsterMart = new VendingMachine();
        monsterMart.run();
    }

    public Product findProductByName(String name) {
        for (Product p : products) if (p.getName().equals(name)) return p;
        return null;
    }

    public void initializeProducts() {
        products.add(new Product("Air Putih", 6000, 20));
        products.add(new Product("Teh Botol", 7000, 15));
        products.add(new Product("Nescafe Kaleng", 8000, 12));
        products.add(new Product("Pocari Sweat", 10000, 10));
        products.add(new Product("Buavita", 9000, 8));
        products.add(new Product("Chitato Lite", 6000, 10));
        products.add(new Product("Roma Kelapa", 10000, 12));
        products.add(new Product("Silverqueen", 20000, 10));
        products.add(new Product("Roma Sari Gandum", 8000, 15));
        products.add(new Product("Sari Roti", 6000, 14));
    }

    public void printMenu() {
        String menu = new String();

        menu += "\n\n" + "=============== Menu ===============" + "\n";
        menu += "#\tNama Produk\tStock\tHarga\n";

        for (int i = 0; i < products.size(); i++) {
            Product p = products.get(i);
            menu += (i + 1) + "\t" + p.getName() + "\t" + p.getStock() + "\t" + p.getPrice() + "\n";
        }

        menu += "====================================\n";
        menu += "Pilih dari (1 - " + products.size() + ") ketik 0 untuk balik ke menu: ";
        System.out.print(menu);
    }

    public void processOrder(Scanner scanner) {
        boolean isOrdering = true;
        Transaction transaction = new Transaction();
        int orderSelection;
        while(isOrdering) {
            transaction.printReceipt();
            System.out.print("1. Tambah Pesanan\n2. Hapus Pesanan\n3. Bayar Pesanan\n4. Batal\nPilih dari (1-4): ");
            orderSelection = scanner.nextInt();
            int menuSelection;
            switch (orderSelection) {
                case 1:
                    boolean ordering = true;
                    while(ordering) {
                        int count = 0;
                        transaction.printReceipt();
                        printMenu();
                        menuSelection = scanner.nextInt();
                        if(menuSelection < 0 || menuSelection > products.size()) {
                            System.out.println("Pilihan tidak valid, silahkan coba lagi");
                            continue;
                        }
                        if(menuSelection == 0) {
                            ordering = false;
                            break;
                        }
                        Product p = products.get(menuSelection - 1);
                        System.out.print("Jumlah: ");
                        count = scanner.nextInt();
                        if(count <= 0) {
                            System.out.println("Jumlah tidak valid, silahkan cobal lagi");
                            continue;
                        } else if(!p.checkStock(count)) {
                            System.out.println("Stok tidak mencukupi, coba pesan lagi");
                            continue;
                        } else {
                            transaction.addOrder(new Product(p.getName(), p.getPrice(), count));
                            p.reduceStock(count);
                        }
                        if(p.getStock() == 0) System.out.println("\nProduk " + p.getName() + " habis, segera isi stok\n");
                    }
                    break;
                case 2:
                    boolean removing = true;
                    while(removing) {
                        transaction.printReceipt();
                        System.out.print("Pilih dari (1 - " + transaction.getProductCount() + ") ketik 0 untuk balik ke menu: ");
                        menuSelection = scanner.nextInt(); 
                        if(menuSelection < 0 || menuSelection > transaction.getProductCount()) {
                            System.out.println("Pilihan tidak valid, silahkan coba lagi");
                            continue;
                        }
                        if(menuSelection == 0) {
                            removing = false;
                            break;
                        }
                        Product p = transaction.getOrder(menuSelection - 1);
                        findProductByName(p.getName()).addStock(p.getStock());
                        p = null;
                        transaction.removeOrder(menuSelection - 1);
                    }
                    break;
                case 3:
                    transaction.pay(scanner);
                    transactions.add(transaction);
                    isOrdering = false;
                    break;
                case 4:
                    isOrdering = false;
                    break;
                default:
                    System.out.println("Pilihan tidak valid, silahkan coba lagi");
                    break;
            }
        }
    }

    public void showLog() {
        System.out.println("\n=============== Log Transaksi ===============");

        if (transactions.isEmpty()) System.out.println("Belum ada transaksi yang tercatat.");
        else {
            for (Transaction t : transactions) {
                t.printReceipt();
            }
        }
        System.out.println("\n\n=============================================\n");
    }

    public void run() {
        Scanner scanner = new Scanner(System.in);
        boolean isRunning = true;

        while(isRunning) {
            System.out.println("\n\n========== Monster Mart ==========");
            System.out.println("1. Pesan Produk");
            System.out.println("2. Lihat log transaksi");
            System.out.println("3. Keluar");
            System.out.println("==================================");
            System.out.print("Pilihan dari (1-3): ");
            
            int mainMenuSelection = scanner.nextInt();

            switch (mainMenuSelection) {
                case 1:
                    processOrder(scanner);
                    break;
                case 2:
                    showLog();
                    break;
                case 3:
                    isRunning = false;
                    System.out.println("\nTerima kasih telah menggunakan Monster Mart!");
                    break;
                default:
                    System.out.println("Pilihan tidak valid, silakan coba lagi.");
                    break;
            }
        }
        scanner.close();
    }
}