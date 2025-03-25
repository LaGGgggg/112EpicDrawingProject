class Base{
    public:
        ID addObject(ObjType otype) {
            switch (otype) {
            case OBJ_DOT:
                m_dotStorage.add(dot());
                return m_dotStorage.getElementPosition(m_dotStorage.size() - 1).getID();
                break;
            case OBJ_SEG:
                m_segmentStorage.add(segment(dot(), dot()));
                return m_segmentStorage.getElementPosition(m_segmentStorage.size() - 1).getID();
                break;
            }
    
            default:
                std::cerr << "Invalid object type" << std::endl;
        };
    
        SRPResult setRelativePos(Storage<ID>& objects, RelativePosType rpt) {
            // Проверка на корректность пожеланий пользователя
            
            const double errorThreshold = 1e-6;
    
            while ( getError( objects, rpt) > errorThreshold )  /* Условие необходимости продолжения процедуры поиска значений параметров*/ {
    
                // Выбираем как изменить параметры объектов 
                // (для этого надо уметь вычислять частные производные 
                // от величины ошибки)
    
                // Меняем параметры 
                // (для этого надо реализовать методы, 
                // модифицирующие положение точек и отрезков)
                // Оцениваем как изменилась ситуации с точки зрения 
                // выполнения пожеланий пользователя
            }		
        }
    
        double getError(Storage<ID>& objects, RelativePosType rpt);
    
        int getObjChildren(ID id, Storage<ID>& childIds){
    
        }
    
        int getObjParams(ID id, Storage<double>& params) {
            for (size_t k = 0; k < m_dotStorage.size(); ++k) {
                if (m_dotStorage.getElementPosition(k).getID() == id) {
                    params.add(m_dotStorage.getElementPosition(k).getx());
                    params.add(m_dotStorage.getElementPosition(k).gety());
                    return 0;
                }
            }
            return -1;
        }
    
        
    private:
        struct dotinfo{
            ID id;
            dot* data
        }
    
        struct seginfo{
            ID id;
            segment* data;
        }
        Storage<dotinfo> m_dotStorage;
        Storage<seginfo> m_segmentStorage;
    };    
