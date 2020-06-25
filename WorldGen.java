import java.util.Scanner;

public class WorldGen {
  private int x;
  
  private int y;
  
  public WorldGen() {
    Scanner sc = new Scanner(System.in);
    System.out.println("kérek 2 számot (ez lesz a világ mérete)");
    boolean repeat = true;
    while (repeat) {
      String input = sc.nextLine();
      String[] dimenziok = input.split(" ");
      if (dimenziok.length > 2) {
        System.out.println("há ez jó sok valami vót");
        continue;
      } 
      if (dimenziok.length == 2) {
        try {
          this.x = Integer.parseInt(dimenziok[0]);
          this.y = Integer.parseInt(dimenziok[1]);
          if (this.x < 1 || this.y < 1) {
            System.out.println("nem pozitív méretű világ? dik. ilyen nincs. újra bruh");
            continue;
          } 
          System.out.println("" + this.x + "*" + this.x + " méretű világ létrehozva");
          repeat = false;
        } catch (NumberFormatException ex) {
          System.out.println("számokat írjál nekem gec");
        } 
        continue;
      } 
      try {
        this.x = Integer.parseInt(dimenziok[0]);
        System.out.println("há ez nem vót valami sok szám");
      } catch (NumberFormatException ex) {
        System.out.println("more, ez nem hogy nem elég szám, de még csak nem is szám");
      } 
    } 
  }
  
  public World createWorld() {
    return new World(this.x, this.y);
  }
}
