import xml.etree.ElementTree as ET

def rebalance_economy(file_path, output_path):
    tree = ET.parse(file_path)
    root = tree.getroot()

    # Списки префиксов, которые нужно "придушить"
    super_rare = ['OH_altin', 'OH_6b13', 'OH_6B43', 'OH_6b45', 'OH_Full_Heavy', 'OH_ronin']
    uncommon = ['OH_mich', 'OH_ops_core', 'OH_Tactical_vest', 'OH_Plate_Carrier']
    accessories = ['OH_Toppouches', 'OH_pouches', 'OH_mag_pouche', 'OH_pouch']

    for item in root.findall('type'):
        name = item.get('name')
        
        # Логика для очень редких (Алтыны, Тяжелая броня, Ронины)
        if any(pref in name for name in [name] for pref in super_rare):
            item.find('nominal').text = '1'
            item.find('min').text = '1'
        
        # Логика для шлемов и жилетов среднего класса
        elif any(pref in name for name in [name] for pref in uncommon):
            item.find('nominal').text = '2'
            item.find('min').text = '1'
            
        # Логика для подсумков (чтобы не валялись на каждом шагу)
        elif any(pref in name for name in [name] for pref in accessories):
            item.find('nominal').text = '2'
            item.find('min').text = '1'

    # Сохраняем
    tree.write(output_path, encoding='utf-8', xml_declaration=True)
    print(f"Балансировка завершена. Файл сохранен в {output_path}")

if __name__ == "__main__":
    rebalance_economy('types.xml', 'types_balanced.xml')