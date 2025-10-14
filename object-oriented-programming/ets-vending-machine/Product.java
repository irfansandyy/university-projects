public class Product {
    private String name;
    private int price;
    private int stock;

    public Product(String name, int price, int stock) {
        this.name = name;
        this.price = price;
        this.stock = stock;
    }

    public String getName() {
        return name;
    }

    public int getPrice() {
        return price;
    }

    public int getStock() {
        return stock;
    }

    public boolean checkStock(int stock) {
        return this.stock >= stock;
    }

    public void addStock(int stock) {
        this.stock += stock;
    }

    public boolean reduceStock(int stock) {
        if (checkStock(stock)) {
            this.stock -= stock;
            return true;
        }
        return false;
    }
}