package commands;

import core.Data;

public class Help implements Command {
  public String execute(String[] strs, Data data) {
    return "A játék 2 játékossal játszható.\nMindkét játékos amazonokat hozhat létre és irányíthat, amelyek lovagolhatnak dinoszauruszokon, tárgyakat vehetnek fel, és ezek segítségével a szart is kiölhetik egymásból.\nA játék világa mezőkből áll, ezekre koordinátákkal lehet hivatkozni.\nA játék körökben játszható.\nJátékmódtól függően korlátozva van, hogy egy játékos összesen hány amazont hozhat létre, egyszerre hány élő amazonja lehet a pályán, és hány lépést tehet egy-egy körben.\nA cél az ellenfél összes lehetséges amazonját elpusztítani.\nAz győz, aki nem veszít.\nA játékban minden tevékenység parancsokkal végezhető.\nAz elérhető parancsok az alábbiak:\nexit: most magyarázzam?\nnew [név]: létrehoz egy amazont a megadott névvel. Az amazonok játékosnak megfelelően a világ átellenes sarkaiban spawnolnak.\nselect [név]: kiválasztja a megadott amazont.\nattack [név]: a kiválaszott amazon megtámadja a megadott amazont.\nmove [x] [y]: a kiválasztott amazon a megadott koordinátára mozdul.\nlookaround: a kiválasztott amazon megvizsgálja környezetét.\ntame: a kiválasztott amazon beidomítja a környezetében lévő dinoszauruszt.\ngeton: a kiválaszott amazon felszáll a dinoszauruszára.getoff: a kiválasztott amazon leszáll a dinoszauruszáról.\nstatus: a kiválasztott amazon aktuális adatai.\npickup [itemnév]: a kiválasztott amazon felveszi a megadott tárgyat.\ndrop [itemnév]: a kiválasztott amazon eldobja a megadott tárgyat.\nequip [fegyvernév]: a kiválasztott amazon kézbe veszi a megadott fegyvert.\nsteps: kiírja az aktuális játékos lehetőségeit, állását.end: a kör befejezése.\nlist: az aktuális játékos összes amazonjának listája.\n";
  }
}
