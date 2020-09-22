package Build_Design_Pattern;

@SuppressWarnings({"unused", "RedundantSuppression"})
public class BankAccount {

    public static void main(String[] args) {
        //BAD!
//        BankAccount account = new BankAccount(456L, "Marge", "Springfield", 100.00, 2.5);
//        BankAccount anotherAccount = new BankAccount(789L, "Homer", null, 2.5, 100.00);  //Oops!
        BankAccount account =
                new Builder()
                        .accountNumber(1234L)
                        .owner("Marge")
                        .branch("Springfield")
                        .balance(100)
                        .interestRate(2.5)
                        .build();
        BankAccount anotherAccount =
                new Builder()
                        .accountNumber(5555L)
                        .owner("Homer")
                        .branch("Springfield")
                        .balance(100)
                        .interestRate(2.5)
                        .build();


    }

    private long accountNumber; //This is important, so we'll pass it to the constructor.
    private String owner;
    private String branch;
    private double balance;
    private double interestRate;


    //BAD!
//    public BankAccount(long accountNumber, String owner, String branch, double balance, double interestRate) {
//        this.accountNumber = accountNumber;
//        this.owner = owner;
//        this.branch = branch;
//        this.balance = balance;
//        this.interestRate = interestRate;
//    }


    public static class Builder {
        private long accountNumber; //This is important, so we'll pass it to the constructor.
        private String owner;
        private String branch;
        private double balance;
        private double interestRate;

        public Builder accountNumber(long accountNumber) {
            this.accountNumber = accountNumber;
            return this;
        }

        public Builder owner(String owner) {
            this.owner = owner;
            return this;  //By returning the builder each time, we can create a fluent interface.
        }

        public Builder branch(String branch) {
            this.branch = branch;
            return this;
        }

        public Builder balance(double balance) {
            this.balance = balance;
            return this;
        }

        public Builder interestRate(double interestRate) {
            this.interestRate = interestRate;
            return this;
        }

        public BankAccount build() {
            //Here we create the actual bank account object, which is always in a fully initialised state when it's returned.
            BankAccount account = new BankAccount();  //Since the builder is in the BankAccount class, we can invoke its private constructor.
            account.accountNumber = this.accountNumber;
            account.owner = this.owner;
            account.branch = this.branch;
            account.balance = this.balance;
            account.interestRate = this.interestRate;
            return account;
        }
    }

    //Fields omitted for brevity.
    private BankAccount() {
        //Constructor is now private.
    }
    //Getters and setters omitted for brevity.

}
