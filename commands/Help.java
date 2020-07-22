package commands;

import core.Data;
import units.Report;

public class Help implements Command {
    @Override
    public Report execute(String[] strs, Data data) {
        return new Report("A játék körökre osztott és 2 játékossal játszható.\n" +
                "A körök lépésekre vannak osztva. Bizonyos parancsok lépésekbe kerülnek, mások nem.\n" +
                "A játékosok amazonokat hozhatnak létre és irányíthatnak. Mindkét játékosnak meg van határozva a maximálisan létrehozható és az egy időben élő amazonok száma.\n" +
                "A térkép négyzetekre, \"mezőkre\" van osztva. A mezőkön különböző tárgyak és élőlények találhatóak.\n" +
                "A játék legfontosabb tárgyai a fegyverek. Jelenleg 5 féle fegyver érhető el: pisztoly, gépkatana, shotgun, minigun és rocket launcher. Ezek mind-mind más sebzéssel rendelkeznek.\n" +
                "A mezőkön spawnolnak dinók is. Az amazonok ezeket beidomíthatják és meglovagolhatják, növelve ezzel a védelmüket.\n" +
                "A játékosoknak vannak közös ellenségeik: a braindrainerek. A braindrainerek megtámadnak akárkit, aki a mezőjükre lép. Minden kör végén átléphetnek egy szomszédos mezőre.\n" +
                "Az elérhető fegyverek és számuk, a térkép mérete, a dinók, amazonok, és braindrainerek száma játékmódfüggő, spawnjuk randomizált.\n" +
                "A játék célja, hogy a játékos megölje ellenfele összes lehetséges amazonját.\n" +
                "Parancsok, melyek lépésbe kerülnek:\n" +
                "\"new\" <név>: létrehoz egy amazont a megadott névvel. Az amazonok játékosnak megfelelően a világ átellenes sarkaiban spawnolnak. 1 lépésbe kerül.\n" +
                "\"move\" <x> <y>: a kiválasztott amazon a megadott koordinátájú mezőre megy. Ez csak szomszédos mező lehet. 1 lépésbe kerül.\n" +
                "\"tame\": a kiválasztott amazon beidomítja a környezetében lévő dinoszauruszt (több esetében a legnagyobb élettel rendelkezőt). 1 lépésbe kerül.\n" +
                "\"pickup\" <név>: a kiválasztott amazon felveszi a megadott tárgyat. 1 lépésbe kerül.\n" +
                "\"drop\" <név>: a kiválasztott amazon eldobja a megadott tárgyat. 1 lépésbe kerül.\n" +
                "\"attack\" <név>: a kiválaszott amazon megtámadja a megadott amazont. 1 lépésbe kerül.\n" +
                "Az ingyenes parancsok:\n" +
                "\"steps\": az aktuális játékos lehetőségei, állása.\n" +
                "\"list\": az aktuális játékos összes amazonjának listája.\n" +
                "\"select\" <név>: kiválasztja a megadott amazont.\n" +
                "\"status\": a információ a kiválasztott amazonról.\n" +
                "\"lookaround\": a kiválasztott amazon körbenéz.\n" +
                "\"geton\": a kiválaszott amazon felszáll a dinoszauruszára.\n" +
                "\"getoff\": a kiválasztott amazon leszáll a dinoszauruszáról.\n" +
                "\"equip\" <név>: a kiválasztott amazon kézbe veszi a megadott fegyverét.\n" +
                "\"end\": a kör befejezése. A fel nem használt lépések elvesznek.\n" +
                "\"exit\": most magyarázzam?\n", false);
    }
}